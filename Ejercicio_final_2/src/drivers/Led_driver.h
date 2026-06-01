#ifndef     LED_DRIVER_H
#define     LED_DRIVER_H

/* ---------------- FUNCIONES PÚBLICAS ---------------- */
void led_driver_init(void);
void led_driver_on(void);
void led_driver_off(void);
bool led_driver_get_status(void);
