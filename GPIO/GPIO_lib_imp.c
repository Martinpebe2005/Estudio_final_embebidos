// ─────────────────────────────────────────────────────────────
// GPIO LIBRARY
// Funciones básicas para controlar una salida digital.
// ─────────────────────────────────────────────────────────────

#include "gpio_lib.h"

#include "driver/gpio.h"

// ─────────────────────────────────────────────────────────────
// DEFINES
// GPIO utilizado como salida.
// CAMBIAR según la aplicación.
// ─────────────────────────────────────────────────────────────

#define OUTPUT_GPIO GPIO_NUM_2

// ─────────────────────────────────────────────────────────────
// VARIABLE GLOBAL
// Guarda el estado actual del GPIO.
// ─────────────────────────────────────────────────────────────

static int gpio_state = 0;

// ─────────────────────────────────────────────────────────────
// gpio_lib_init()
// Configura el GPIO como salida digital.
// Debe ejecutarse una sola vez.
// ─────────────────────────────────────────────────────────────

void gpio_lib_init(void)
{
    gpio_set_direction(OUTPUT_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(OUTPUT_GPIO, 0);

    gpio_state = 0;
}

// ─────────────────────────────────────────────────────────────
// gpio_lib_on()
// Activa la salida digital.
// ─────────────────────────────────────────────────────────────

void gpio_lib_on(void)
{
    gpio_set_level(OUTPUT_GPIO, 1);

    gpio_state = 1;
}

// ─────────────────────────────────────────────────────────────
// gpio_lib_off()
// Desactiva la salida digital.
// ─────────────────────────────────────────────────────────────

void gpio_lib_off(void)
{
    gpio_set_level(OUTPUT_GPIO, 0);

    gpio_state = 0;
}

// ─────────────────────────────────────────────────────────────
// gpio_lib_toggle()
// Invierte el estado actual del GPIO.
// ─────────────────────────────────────────────────────────────

void gpio_lib_toggle(void)
{
    gpio_state = !gpio_state;

    gpio_set_level(OUTPUT_GPIO, gpio_state);
}