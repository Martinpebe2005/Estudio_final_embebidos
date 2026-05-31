#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

/* ---------------- INICIALIZACIÓN ---------------- */

// Inicializa el servicio ADC
void adc_service_init(void);

/* ---------------- LECTURAS ---------------- */

// Retorna voltaje promedio en mV
float adc_read_mv(void);

// Conversión para LM35
float adc_read_lm35(void);

// Conversión a porcentaje
float adc_read_percentage(void);

#endif