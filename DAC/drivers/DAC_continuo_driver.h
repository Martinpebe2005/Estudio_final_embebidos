#ifndef DAC_CONTINUOUS_DRIVER_H
#define DAC_CONTINUOUS_DRIVER_H

#include <stdint.h>

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el DAC continuo
void dac_continuo_init(void);

/* ---------------- ESCRITURA ---------------- */
// Escribe una tabla y el DAC la repite automáticamente
void dac_continuo_write_table(uint8_t *tabla, uint32_t size);

#endif