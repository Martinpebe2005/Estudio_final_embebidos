#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H
#include <stdint.h>
/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el servicio del timer
void timer_service_init(void);

/* ---------------- LECTURA ---------------- */
// Compara el tiempo actual contra el último tiempo guardado
uint8_t timer_service_has_elapsed(uint64_t *last, uint64_t period_us);
