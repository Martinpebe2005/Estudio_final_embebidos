#ifndef DS1307_SERVICE_H
#define DS1307_SERVICE_H

#include <stdint.h>

/* ---------------- CONVERSIONES ---------------- */

uint8_t decimal_a_bcd(uint8_t decimal);

uint8_t bcd_a_decimal(uint8_t bcd);

/* ---------------- ESCRITURA ---------------- */

void ds1307_escribir_hora(void);

/* ---------------- LECTURA ---------------- */

void ds1307_leer_hora(void);

#endif