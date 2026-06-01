#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el timer base
void timer_driver_init(void);

/* ---------------- LECTURA ---------------- */
// Lee el tiempo actual en microsegundos
uint64_t timer_driver_get_time_us(void);

#endif