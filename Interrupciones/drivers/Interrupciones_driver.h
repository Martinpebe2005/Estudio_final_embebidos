#ifndef INTERRUPT_DRIVER_H
#define INTERRUPT_DRIVER_H

#include <stdint.h>

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el pin con interrupción
void interrupt_driver_init(void);

/* ---------------- LECTURA ---------------- */
// Retorna 1 si ocurrió una interrupción
uint8_t interrupt_driver_get_flag(void);

// Retorna cuántas interrupciones han ocurrido
uint32_t interrupt_driver_get_count(void);

/* ---------------- ESCRITURA ---------------- */
// Limpia la bandera de interrupción
void interrupt_driver_clear_flag(void);

#endif