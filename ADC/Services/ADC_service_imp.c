/******************************************************************************
 * ADC SERVICE
 * Procesa lecturas ADC para la aplicación
 ******************************************************************************/

#include "adc_service.h"
#include "adc_driver.h"

/* ---------------- INICIALIZACIÓN ---------------- */

void adc_service_init(void)
{
    adc_driver_init();
}

/* ---------------- VOLTAJE PROMEDIO ---------------- */

float adc_read_mv(void)
{
    int suma = 0;

    // Promediar 10 muestras para reducir ruido

    for(int i = 0; i < 10; i++)
    {
        suma += adc_driver_read_mv();
    }

    return (float)(suma / 10);
}

/* ---------------- LM35 ---------------- */

float adc_read_lm35(void)
{
    float mv = adc_read_mv();

    // LM35: 10 mV = 1 °C

    return mv / 10.0f;
}

/* ---------------- PORCENTAJE ---------------- */

float adc_read_percentage(void)
{
    float mv = adc_read_mv();

    // Escala 0 - 3300 mV a 0 - 100 %

    return mv * 100.0f / 3300.0f;
}