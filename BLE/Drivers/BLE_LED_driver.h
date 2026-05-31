#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

/* ---------------- FUNCIONES PÚBLICAS ---------------- */

void led_driver_init(uint8_t pin);
void led_driver_on(void);
void led_driver_off(void);
void led_driver_toggle(void);

#endif