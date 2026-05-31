/******************************************************************************
 * EJEMPLO ADC
 * Lectura de temperatura usando LM35
 ******************************************************************************/

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ADC_services.h"

void app_main(void)
{
    /* ---------------- INICIALIZACIÓN ---------------- */

    adc_service_init();

    /* ---------------- LOOP PRINCIPAL ---------------- */

    while(1)
    {
        float temperatura =
            adc_read_lm35();

        printf(
            "Temperatura: %.2f °C\n",
            temperatura
        );

        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );
    }
}