/******************************************************************************
 * ADC DRIVER
 * Maneja directamente el hardware ADC del ESP32
 ******************************************************************************/

#include "adc_driver.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

/* ---------------- CONFIGURACIÓN ---------------- */

// Cambiar si se utiliza otro pin ADC
#define ADC_CANAL ADC_CHANNEL_6

/* ---------------- VARIABLES PRIVADAS ---------------- */

static adc_oneshot_unit_handle_t adc1_handle;
static adc_cali_handle_t adc1_cali_handle;

/* ---------------- INICIALIZACIÓN ---------------- */

void adc_driver_init(void)
{
    // Inicializar unidad ADC

    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1
    };

    adc_oneshot_new_unit(
        &unit_cfg,
        &adc1_handle
    );

    // Configurar canal ADC

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };

    adc_oneshot_config_channel(
        adc1_handle,
        ADC_CANAL,
        &chan_cfg
    );

    // Configurar calibración

    adc_cali_line_fitting_config_t cali_cfg = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT
    };

    adc_cali_create_scheme_line_fitting(
        &cali_cfg,
        &adc1_cali_handle
    );
}

/* ---------------- LECTURA CRUDA ---------------- */

int adc_driver_read_raw(void)
{
    int raw;

    adc_oneshot_read(
        adc1_handle,
        ADC_CANAL,
        &raw
    );

    return raw;
}

/* ---------------- LECTURA EN mV ---------------- */

int adc_driver_read_mv(void)
{
    int raw;
    int mv;

    adc_oneshot_read(
        adc1_handle,
        ADC_CANAL,
        &raw
    );

    adc_cali_raw_to_voltage(
        adc1_cali_handle,
        raw,
        &mv
    );

    return mv;
}