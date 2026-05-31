// ─────────────────────────────────────────────────────────────
// LIBRERÍAS
// ─────────────────────────────────────────────────────────────

#include "adc_lib.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

// ─────────────────────────────────────────────────────────────
// DEFINES
// Configuración general del ADC
// ─────────────────────────────────────────────────────────────

#define ADC_UNIT_USED      ADC_UNIT_1
#define ADC_CHANNEL_USED   ADC_CHANNEL_6
#define ADC_ATTEN_USED     ADC_ATTEN_DB_12
#define ADC_SAMPLES        10

// ─────────────────────────────────────────────────────────────
// VARIABLES GLOBALES
// Handles del ADC y de la calibración
// ─────────────────────────────────────────────────────────────

static adc_oneshot_unit_handle_t adc_handle;
static adc_cali_handle_t adc_cali_handle;

// ─────────────────────────────────────────────────────────────
// adc_lib_init()
// Inicializa el ADC y configura el canal a utilizar.
// También crea el esquema de calibración.
// Debe ejecutarse una sola vez al iniciar el programa.
// ─────────────────────────────────────────────────────────────

void adc_lib_init(void)
{
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_USED,
    };

    adc_oneshot_new_unit(&unit_cfg, &adc_handle);

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten    = ADC_ATTEN_USED,
    };

    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_USED, &chan_cfg);

    adc_cali_line_fitting_config_t cali_cfg = {
        .unit_id  = ADC_UNIT_USED,
        .atten    = ADC_ATTEN_USED,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    adc_cali_create_scheme_line_fitting(&cali_cfg, &adc_cali_handle);
}

// ─────────────────────────────────────────────────────────────
// adc_lib_read_raw()
// Lee el ADC y retorna el valor RAW promedio.
// Útil para depuración o cálculos manuales.
// ─────────────────────────────────────────────────────────────


int adc_lib_read_raw(void)
{
    int raw = 0;
    int suma = 0;

    for (int i = 0; i < ADC_SAMPLES; i++) {
        adc_oneshot_read(adc_handle, ADC_CHANNEL_USED, &raw);
        suma += raw;
    }

    return suma / ADC_SAMPLES;
}

// ─────────────────────────────────────────────────────────────
// adc_lib_read_mv()
// Lee el ADC y retorna el voltaje promedio en mV.
// Utiliza la calibración interna del ESP32.
// ─────────────────────────────────────────────────────────────

int adc_lib_read_mv(void)
{
    int raw = 0;
    int mv = 0;
    int suma = 0;

    for (int i = 0; i < ADC_SAMPLES; i++) {
        adc_oneshot_read(adc_handle, ADC_CHANNEL_USED, &raw);
        adc_cali_raw_to_voltage(adc_cali_handle, raw, &mv);
        suma += mv;
    }

    return suma / ADC_SAMPLES;
}

// ─────────────────────────────────────────────────────────────
// adc_lib_read_percent()
// Convierte la lectura a porcentaje.
// Pensado para potenciómetros de 0 a 3.3V.
// ─────────────────────────────────────────────────────────────

float adc_lib_read_percent(void)
{
    int mv = adc_lib_read_mv();

    return (mv * 100.0f) / 3300.0f;
}