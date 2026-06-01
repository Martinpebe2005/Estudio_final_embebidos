#include "led_driver.h"
#include "driver/gpio.h"

static uint8_t Led_pin = 2;


void led_driver_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << Led_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);
    gpio_set_level(Led_pin, 0);
}

void led_driver_on(void)
{
    gpio_set_level(Led_pin, 1);
}

void led_driver_off(void)
{
    gpio_set_level(Led_pin, 0);
}

bool led_driver_get_status(void)
{
    return gpio_get_level(Led_pin);
}