// ─────────────────────────────────────────────────────────────
// BLE NUS LIBRARY
// Librería para usar Bluetooth Low Energy con Nordic UART Service.
// RX: el celular/PC escribe comandos hacia el ESP32.
// TX: el ESP32 responde usando notificaciones BLE.
// ─────────────────────────────────────────────────────────────

#include "ble_nus_lib.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "esp_log.h"
#include "esp_err.h"
#include "esp_bt.h"
#include "nvs_flash.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"

#include "host/ble_hs.h"
#include "host/ble_gap.h"
#include "host/ble_gatt.h"
#include "host/ble_uuid.h"

#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

// ─────────────────────────────────────────────────────────────
// DEFINES
// Cambia aquí el GPIO del LED y el nombre BLE visible.
// ─────────────────────────────────────────────────────────────

#define LED_GPIO     GPIO_NUM_26          // CAMBIAR: GPIO del LED
#define DEVICE_NAME  "ESP32-NUS"          // CAMBIAR: nombre BLE

// ─────────────────────────────────────────────────────────────
// VARIABLES GLOBALES
// Guardan estado de conexión, notificaciones y handles BLE.
// ─────────────────────────────────────────────────────────────

static const char *TAG = "BLE_NUS_LIB";

static uint8_t own_addr_type;
static uint16_t conn_handle = BLE_HS_CONN_HANDLE_NONE;
static uint16_t nus_tx_val_handle;
static bool notify_enabled = false;

// ─────────────────────────────────────────────────────────────
// UUIDs oficiales Nordic UART Service
// No modificar si quieres compatibilidad con apps tipo nRF Connect.
//
// Service: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
// RX:      6E400002-B5A3-F393-E0A9-E50E24DCCA9E
// TX:      6E400003-B5A3-F393-E0A9-E50E24DCCA9E
//
// En NimBLE se escriben en little-endian.
// ─────────────────────────────────────────────────────────────

static const ble_uuid128_t nus_service_uuid =
    BLE_UUID128_INIT(0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0,
                     0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e);

static const ble_uuid128_t nus_rx_uuid =
    BLE_UUID128_INIT(0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0,
                     0x93, 0xf3, 0xa3, 0xb5, 0x02, 0x00, 0x40, 0x6e);

static const ble_uuid128_t nus_tx_uuid =
    BLE_UUID128_INIT(0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0,
                     0x93, 0xf3, 0xa3, 0xb5, 0x03, 0x00, 0x40, 0x6e);

// ─────────────────────────────────────────────────────────────
// PROTOTIPOS INTERNOS
// Funciones privadas usadas dentro de esta librería.
// ─────────────────────────────────────────────────────────────

static void ble_app_advertise(void);
static void ble_app_on_sync(void);
static void ble_app_on_reset(int reason);
static void ble_host_task(void *param);

static int ble_gap_event_cb(struct ble_gap_event *event, void *arg);
static int nus_rx_access_cb(uint16_t conn_handle_param,
                            uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt,
                            void *arg);
static int nus_tx_access_cb(uint16_t conn_handle_param,
                            uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt,
                            void *arg);

// ─────────────────────────────────────────────────────────────
// ble_nus_send_response()
// Envía texto desde el ESP32 hacia el celular/PC por TX Notify.
// Requiere que el cliente esté conectado y suscrito a notificaciones.
// ─────────────────────────────────────────────────────────────

void ble_nus_send_response(const char *msg)
{
    if (conn_handle == BLE_HS_CONN_HANDLE_NONE || !notify_enabled) {
        ESP_LOGW(TAG, "Cliente no conectado o no suscrito a TX Notify");
        return;
    }

    struct os_mbuf *om = ble_hs_mbuf_from_flat(msg, strlen(msg));

    if (om == NULL) {
        ESP_LOGE(TAG, "No se pudo crear buffer BLE");
        return;
    }

    int rc = ble_gatts_notify_custom(conn_handle, nus_tx_val_handle, om);

    if (rc != 0) {
        ESP_LOGE(TAG, "Error enviando notificacion: %d", rc);
    }
}

// ─────────────────────────────────────────────────────────────
// nus_rx_access_cb()
// Se ejecuta cuando el celular/PC escribe algo en la característica RX.
// Aquí modificas los comandos según tu aplicación.
// En este ejemplo:
// 'E' = encender LED
// 'A' = apagar LED
// ─────────────────────────────────────────────────────────────

static int nus_rx_access_cb(uint16_t conn_handle_param,
                            uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt,
                            void *arg)
{
    uint8_t data[64];
    uint16_t len = 0;

    int rc = ble_hs_mbuf_to_flat(ctxt->om, data, sizeof(data) - 1, &len);

    if (rc != 0) {
        return BLE_ATT_ERR_UNLIKELY;
    }

    data[len] = '\0';

    ESP_LOGI(TAG, "Dato recibido por BLE: %s", data);

    // CAMBIAR AQUÍ: lógica de comandos BLE
    if (len > 0 && data[0] == 'E') {
        gpio_set_level(LED_GPIO, 1);
        ble_nus_send_response("LED encendido");
    }
    else if (len > 0 && data[0] == 'A') {
        gpio_set_level(LED_GPIO, 0);
        ble_nus_send_response("LED apagado");
    }
    else {
        ble_nus_send_response("Error: comando desconocido");
    }

    return 0;
}

// ─────────────────────────────────────────────────────────────
// nus_tx_access_cb()
// Callback de la característica TX.
// TX se usa principalmente para notificaciones desde el ESP32.
// ─────────────────────────────────────────────────────────────

static int nus_tx_access_cb(uint16_t conn_handle_param,
                            uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt,
                            void *arg)
{
    return 0;
}

// ─────────────────────────────────────────────────────────────
// TABLA GATT
// Define el servicio NUS con dos características:
// RX: escritura desde celular/PC hacia ESP32.
// TX: notificaciones desde ESP32 hacia celular/PC.
// ─────────────────────────────────────────────────────────────

static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = &nus_service_uuid.u,
        .characteristics = (struct ble_gatt_chr_def[]) {
            {
                .uuid = &nus_rx_uuid.u,
                .access_cb = nus_rx_access_cb,
                .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_NO_RSP,
            },
            {
                .uuid = &nus_tx_uuid.u,
                .access_cb = nus_tx_access_cb,
                .val_handle = &nus_tx_val_handle,
                .flags = BLE_GATT_CHR_F_NOTIFY,
            },
            { 0 }
        },
    },
    { 0 }
};

// ─────────────────────────────────────────────────────────────
// ble_gap_event_cb()
// Maneja eventos BLE:
// conexión, desconexión, suscripción a notify y fin de advertising.
// ─────────────────────────────────────────────────────────────

static int ble_gap_event_cb(struct ble_gap_event *event, void *arg)
{
    switch (event->type) {

    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status == 0) {
            conn_handle = event->connect.conn_handle;
            ESP_LOGI(TAG, "Cliente conectado");
        } else {
            ESP_LOGW(TAG, "Conexion fallida, reanudando advertising");
            ble_app_advertise();
        }
        return 0;

    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGI(TAG, "Cliente desconectado");
        conn_handle = BLE_HS_CONN_HANDLE_NONE;
        notify_enabled = false;
        ble_app_advertise();
        return 0;

    case BLE_GAP_EVENT_SUBSCRIBE:
        if (event->subscribe.attr_handle == nus_tx_val_handle) {
            notify_enabled = event->subscribe.cur_notify;
            ESP_LOGI(TAG, "TX Notify: %s", notify_enabled ? "ON" : "OFF");
        }
        return 0;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        ble_app_advertise();
        return 0;

    default:
        return 0;
    }
}

// ─────────────────────────────────────────────────────────────
// ble_app_advertise()
// Hace visible el ESP32 como dispositivo BLE.
// Advertising: publica flags y UUID del servicio.
// Scan response: publica el nombre del dispositivo.
// ─────────────────────────────────────────────────────────────

static void ble_app_advertise(void)
{
    struct ble_hs_adv_fields fields;
    struct ble_hs_adv_fields rsp_fields;
    struct ble_gap_adv_params adv_params;

    int rc;

    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
    fields.uuids128 = (ble_uuid128_t *)&nus_service_uuid;
    fields.num_uuids128 = 1;
    fields.uuids128_is_complete = 1;

    rc = ble_gap_adv_set_fields(&fields);

    if (rc != 0) {
        ESP_LOGE(TAG, "Error configurando advertising: %d", rc);
        return;
    }

    memset(&rsp_fields, 0, sizeof(rsp_fields));

    const char *name = ble_svc_gap_device_name();

    rsp_fields.name = (uint8_t *)name;
    rsp_fields.name_len = strlen(name);
    rsp_fields.name_is_complete = 1;

    rc = ble_gap_adv_rsp_set_fields(&rsp_fields);

    if (rc != 0) {
        ESP_LOGE(TAG, "Error configurando scan response: %d", rc);
        return;
    }

    memset(&adv_params, 0, sizeof(adv_params));

    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    rc = ble_gap_adv_start(
        own_addr_type,
        NULL,
        BLE_HS_FOREVER,
        &adv_params,
        ble_gap_event_cb,
        NULL
    );

    if (rc != 0) {
        ESP_LOGE(TAG, "Error iniciando advertising: %d", rc);
    } else {
        ESP_LOGI(TAG, "Advertising iniciado como %s", DEVICE_NAME);
    }
}

// ─────────────────────────────────────────────────────────────
// ble_app_on_sync()
// Se ejecuta cuando el stack BLE ya está listo.
// Obtiene la dirección BLE e inicia advertising.
// ─────────────────────────────────────────────────────────────

static void ble_app_on_sync(void)
{
    int rc = ble_hs_id_infer_auto(0, &own_addr_type);

    if (rc != 0) {
        ESP_LOGE(TAG, "Error obteniendo direccion BLE: %d", rc);
        return;
    }

    ble_app_advertise();
}

// ─────────────────────────────────────────────────────────────
// ble_app_on_reset()
// Se ejecuta si ocurre un reset interno del stack BLE.
// Sirve para depuración.
// ─────────────────────────────────────────────────────────────

static void ble_app_on_reset(int reason)
{
    ESP_LOGE(TAG, "Reset BLE, reason=%d", reason);
}

// ─────────────────────────────────────────────────────────────
// ble_host_task()
// Tarea principal del host NimBLE.
// Se queda corriendo internamente manejando BLE.
// ─────────────────────────────────────────────────────────────

static void ble_host_task(void *param)
{
    nimble_port_run();
    nimble_port_freertos_deinit();
}

// ─────────────────────────────────────────────────────────────
// ble_nus_init()
// Inicializa NVS, libera Bluetooth Classic, configura LED,
// inicializa NimBLE, registra servicios GATT e inicia la tarea BLE.
// Llamar una sola vez desde app_main().
// ─────────────────────────────────────────────────────────────

void ble_nus_init(void)
{
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_GPIO, 0);

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    ESP_ERROR_CHECK(nimble_port_init());

    ble_svc_gap_init();
    ble_svc_gatt_init();

    ble_svc_gap_device_name_set(DEVICE_NAME);

    ble_hs_cfg.sync_cb = ble_app_on_sync;
    ble_hs_cfg.reset_cb = ble_app_on_reset;

    ESP_ERROR_CHECK(ble_gatts_count_cfg(gatt_svr_svcs));
    ESP_ERROR_CHECK(ble_gatts_add_svcs(gatt_svr_svcs));

    nimble_port_freertos_init(ble_host_task);
}