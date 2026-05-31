#include "led_driver.h"
#include "driver/gpio.h"

/* ---------------- VARIABLES PRIVADAS ---------------- */

static uint8_t led_pin = 2;
static uint8_t led_state = 0;

/* ---------------- INICIALIZACIÓN ---------------- */

void led_driver_init(uint8_t pin)
{
    led_pin = pin;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << led_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);
    gpio_set_level(led_pin, 0);
}

/* ---------------- ESCRITURA ---------------- */

void led_driver_on(void)
{
    led_state = 1;
    gpio_set_level(led_pin, led_state);
}

void led_driver_off(void)
{
    led_state = 0;
    gpio_set_level(led_pin, led_state);
}

void led_driver_toggle(void)
{
    led_state = !led_state;
    gpio_set_level(led_pin, led_state);
}