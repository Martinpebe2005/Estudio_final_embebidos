#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

/* ---------------- INICIALIZACIÓN ---------------- */

// Inicializa el ADC y la calibración
void adc_driver_init(void);

/* ---------------- LECTURA ---------------- */

// Retorna lectura cruda del ADC
int adc_driver_read_raw(void);

// Retorna lectura en milivoltios
int adc_driver_read_mv(void);

#endif