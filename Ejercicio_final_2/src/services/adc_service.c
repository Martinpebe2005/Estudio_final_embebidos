/******************************************************************************
 * ADC SERVICE
 * Procesa lecturas ADC para la aplicación
 ******************************************************************************/

#include "adc_service.h"
#include "adc_driver.h"

/* ---------------- INICIALIZACIÓN ---------------- */

void MQ135_service_init(void)
{
    adc_driver_init();
}

/* ---------------- PORCENTAJE ---------------- */

float MQ135_read_percentage(void)
{
    float mv = adc_read_mv();

    // Escala 0 - 3300 mV a 0 - 100 %

    return mv * 100.0f / 3300.0f;
}