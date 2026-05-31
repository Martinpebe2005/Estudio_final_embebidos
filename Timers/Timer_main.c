#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "timer_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Tiempo entre eventos
#define PERIOD_1S_US 1000000

/* ---------------- VARIABLES PRIVADAS ---------------- */
// Guarda el último tiempo registrado
static uint64_t last_time = 0;

/* ---------------- LOOP PRINCIPAL ---------------- */
// Programa principal
void app_main(void)
{
    timer_service_init();

    while (1) {

        if (timer_service_has_elapsed(&last_time, PERIOD_1S_US)) {
            printf("Paso 1 segundo\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}