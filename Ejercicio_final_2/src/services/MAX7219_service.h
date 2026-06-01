#ifndef MAX7219_SERVICE_H
#define MAX7219_SERVICE_H

#include <stdint.h>

/* ---------------- CONFIGURACIÓN ---------------- */
// Prototipos del servicio MAX7219

void max7219_init(void);
void max7219_write(uint8_t reg, uint8_t dato);
void max7219_show_number_4digits(uint16_t number);

#endif