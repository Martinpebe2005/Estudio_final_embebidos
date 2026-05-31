#ifndef GPIO_LIB_H
#define GPIO_LIB_H

// Inicializa el GPIO
void gpio_lib_init(void);

// Enciende la salida
void gpio_lib_on(void);

// Apaga la salida
void gpio_lib_off(void);

// Invierte el estado actual
void gpio_lib_toggle(void);

#endif