#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pwm_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Cambia estos valores para probar otros porcentajes

#define PWM_BAJO   25
#define PWM_MEDIO  50
#define PWM_ALTO   75
#define TIEMPO_MS  1000

/* ---------------- LOOP PRINCIPAL ---------------- */
// Aplicación principal de prueba del PWM

void app_main(void)
{
    pwm_service_init();

    while (1) {
        printf("PWM: %d%%\n", PWM_BAJO);
        pwm_service_set_percent(PWM_BAJO);
        vTaskDelay(pdMS_TO_TICKS(TIEMPO_MS));

        printf("PWM: %d%%\n", PWM_MEDIO);
        pwm_service_set_percent(PWM_MEDIO);
        vTaskDelay(pdMS_TO_TICKS(TIEMPO_MS));

        printf("PWM: %d%%\n", PWM_ALTO);
        pwm_service_set_percent(PWM_ALTO);
        vTaskDelay(pdMS_TO_TICKS(TIEMPO_MS));
    }
}