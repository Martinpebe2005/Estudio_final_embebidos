// ─────────────────────────────────────────────────────────────
// ADC LIBRARY HEADER
// Declaración de funciones públicas
// ─────────────────────────────────────────────────────────────

#ifndef ADC_LIB_H
#define ADC_LIB_H

#include <stdint.h>

void  adc_lib_init(void);
int   adc_lib_read_raw(void);
int   adc_lib_read_mv(void);
float adc_lib_read_percent(void);

#endif