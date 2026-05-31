#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "drivers/dac_continuous_driver/dac_continuous_driver.h"
#include "drivers/dac_oneshot_driver/dac_oneshot_driver.h"

#include "services/waveform_service/waveform_service.h"
#include "services/dac_voltage_service/dac_voltage_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Cambia este define para probar DAC continuo o DAC one-shot
#define USE_DAC_CONTINUOUS  1
#define USE_DAC_ONESHOT     0

/* ---------------- LOOP PRINCIPAL ---------------- */
// Programa principal
void app_main(void)
{
#if USE_DAC_CONTINUOUS

    waveform_service_init(0.5f, 1.65f);

    dac_continuo_init();

    dac_continuo_write_table(waveform_get_sine_table(), NUM_SAMPLES);

#endif

#if USE_DAC_ONESHOT

    dac_oneshot_init();

    dac_set_voltage(1.65f);
    dac_set_voltage(3.3f);
    dac_set_voltage(0.0f);

#endif

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}