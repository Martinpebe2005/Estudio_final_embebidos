// ─────────────────────────────────────────────────────────────
// EJEMPLO DE USO ADC
// Inicializa el ADC y muestra lecturas por consola
// ─────────────────────────────────────────────────────────────

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "adc_lib.h"

void app_main(void)
{
    adc_lib_init();

    while (1) {
        int raw = adc_lib_read_raw();
        int mv = adc_lib_read_mv();
        float percent = adc_lib_read_percent();

        printf("RAW: %d | mV: %d | Porcentaje: %.2f %%\n",
               raw,
               mv,
               percent);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}