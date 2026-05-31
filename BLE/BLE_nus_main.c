#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led_driver.h"
#include "ble_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define LED_PIN 2

/* ---------------- INICIALIZACIÓN ---------------- */

void app_main(void)
{
    led_driver_init(LED_PIN);
    ble_service_init();

    printf("Sistema BLE iniciado\n");
    printf("Comandos disponibles: ON, OFF, TOGGLE\n");

    /* ---------------- LOOP PRINCIPAL ---------------- */

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}