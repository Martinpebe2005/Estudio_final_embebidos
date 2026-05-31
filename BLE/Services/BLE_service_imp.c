#include "ble_service.h"

#include <stdio.h>
#include <string.h>

#include "nvs_flash.h"
#include "esp_log.h"

#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

#include "led_driver.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define DEVICE_NAME "ESP32_BLE"

#define NUS_SERVICE_UUID        0x180D
#define NUS_RX_CHAR_UUID        0x2A39
#define NUS_TX_CHAR_UUID        0x2A37

/* ---------------- VARIABLES PRIVADAS ---------------- */

static const char *TAG = "BLE_SERVICE";

static uint16_t tx_handle;
static uint16_t conn_handle = 0;
static uint8_t is_connected = 0;

/* ---------------- PROTOTIPOS PRIVADOS ---------------- */

static int ble_gap_event(struct ble_gap_event *event, void *arg);
static int ble_gatt_access_cb(uint16_t conn_handle,
                              uint16_t attr_handle,
                              struct ble_gatt_access_ctxt *ctxt,
                              void *arg);

static void ble_advertise(void);
static void ble_on_sync(void);
static void ble_host_task(void *param);

/* ---------------- SERVICIO GATT ---------------- */

static const struct ble_gatt_svc_def gatt_services[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(NUS_SERVICE_UUID),
        .characteristics = (struct ble_gatt_chr_def[]) {
            {
                .uuid = BLE_UUID16_DECLARE(NUS_RX_CHAR_UUID),
                .access_cb = ble_gatt_access_cb,
                .flags = BLE_GATT_CHR_F_WRITE,
            },
            {
                .uuid = BLE_UUID16_DECLARE(NUS_TX_CHAR_UUID),
                .access_cb = ble_gatt_access_cb,
                .val_handle = &tx_handle,
                .flags = BLE_GATT_CHR_F_NOTIFY,
            },
            {0}
        },
    },
    {0}
};

/* ---------------- RECEPCIÓN BLE ---------------- */

static int ble_gatt_access_cb(uint16_t conn_handle,
                              uint16_t attr_handle,
                              struct ble_gatt_access_ctxt *ctxt,
                              void *arg)
{
    char data[50] = {0};

    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
        int len = OS_MBUF_PKTLEN(ctxt->om);

        if (len >= sizeof(data)) {
            len = sizeof(data) - 1;
        }

        ble_hs_mbuf_to_flat(ctxt->om, data, len, NULL);

        ESP_LOGI(TAG, "Dato recibido: %s", data);

        if (strcmp(data, "ON") == 0) {
            led_driver_on();
            ble_service_send("LED ON");
        }
        else if (strcmp(data, "OFF") == 0) {
            led_driver_off();
            ble_service_send("LED OFF");
        }
        else if (strcmp(data, "TOGGLE") == 0) {
            led_driver_toggle();
            ble_service_send("LED TOGGLE");
        }
        else {
            ble_service_send("Comando no valido");
        }
    }

    return 0;
}

/* ---------------- ENVÍO BLE ---------------- */

void ble_service_send(const char *msg)
{
    if (!is_connected) {
        return;
    }

    struct os_mbuf *om = ble_hs_mbuf_from_flat(msg, strlen(msg));

    ble_gatts_notify_custom(conn_handle, tx_handle, om);
}

/* ---------------- EVENTOS BLE ---------------- */

static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type) {

    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status == 0) {
            conn_handle = event->connect.conn_handle;
            is_connected = 1;
            ESP_LOGI(TAG, "Dispositivo conectado");
        } else {
            ble_advertise();
        }
        break;

    case BLE_GAP_EVENT_DISCONNECT:
        is_connected = 0;
        ESP_LOGI(TAG, "Dispositivo desconectado");
        ble_advertise();
        break;

    case BLE_GAP_EVENT_SUBSCRIBE:
        ESP_LOGI(TAG, "Notificaciones configuradas");
        break;

    default:
        break;
    }

    return 0;
}

/* ---------------- ADVERTISING ---------------- */

static void ble_advertise(void)
{
    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;

    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;

    fields.name = (uint8_t *)DEVICE_NAME;
    fields.name_len = strlen(DEVICE_NAME);
    fields.name_is_complete = 1;

    ble_gap_adv_set_fields(&fields);

    memset(&adv_params, 0, sizeof(adv_params));

    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC,
                      NULL,
                      BLE_HS_FOREVER,
                      &adv_params,
                      ble_gap_event,
                      NULL);
}

/* ---------------- SINCRONIZACIÓN ---------------- */

static void ble_on_sync(void)
{
    ble_svc_gap_device_name_set(DEVICE_NAME);
    ble_advertise();
}

/* ---------------- TAREA BLE ---------------- */

static void ble_host_task(void *param)
{
    nimble_port_run();
    nimble_port_freertos_deinit();
}

/* ---------------- INICIALIZACIÓN ---------------- */

void ble_service_init(void)
{
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    nimble_port_init();

    ble_svc_gap_init();
    ble_svc_gatt_init();

    ble_gatts_count_cfg(gatt_services);
    ble_gatts_add_svcs(gatt_services);

    ble_hs_cfg.sync_cb = ble_on_sync;

    nimble_port_freertos_init(ble_host_task);

    ESP_LOGI(TAG, "BLE inicializado");
}