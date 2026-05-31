#ifndef DAC_ONESHOT_DRIVER_H
#define DAC_ONESHOT_DRIVER_H

#include <stdint.h>

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el DAC one-shot
void dac_oneshot_init(void);

/* ---------------- ESCRITURA ---------------- */
// Escribe un valor de 0 a 255 en el DAC
void dac_oneshot_write(uint8_t valor);

#endif