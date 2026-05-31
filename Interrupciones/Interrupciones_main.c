#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "interrupt_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define LOOP_DELAY_MS 50

/* ---------------- INICIALIZACIÓN ---------------- */
// Punto de entrada del programa

void app_main(void)
{
    interrupt_service_init();

    printf("Sistema iniciado\n");

    /* ---------------- LOOP PRINCIPAL ---------------- */
    // Ejecuta continuamente el servicio

    while (1)
    {
        interrupt_service_update();

        vTaskDelay(LOOP_DELAY_MS / portTICK_PERIOD_MS);
    }
}