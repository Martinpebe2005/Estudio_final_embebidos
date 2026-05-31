#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart_driver.h"
#include "uart_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Valores de prueba para enviar por UART

#define DELAY_MS 1000

/* ---------------- LOOP PRINCIPAL ---------------- */
// Aplicación principal

void app_main(void)
{
    float valor1 = 10.5;
    float valor2 = 20.8;
    float cmd;

    uart_driver_init();

    uart_driver_send_string("UART iniciado\n");

    while (1) {
        uart_service_send_values(valor1, valor2);

        cmd = uart_service_receive_cmd();

        if (cmd != -1) {
            printf("Comando recibido: %.2f\n", cmd);
            valor1 = cmd;
        }

        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}