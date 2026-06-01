#include "isr_driver.h"
#include "driver/gpio.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define INTERRUPT_PIN 4

/* ---------------- VARIABLES PRIVADAS ---------------- */

static volatile uint8_t interrupt_flag = 0;
static volatile uint32_t interrupt_count = 0;

/* ---------------- ISR ---------------- */
// Se ejecuta cuando ocurre la interrupción

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    interrupt_flag = 1;
    interrupt_count++;
}

/* ---------------- INICIALIZACIÓN ---------------- */
// Configura el GPIO con interrupción

void interrupt_driver_init(void)
{
    gpio_config_t in_cfg = {
        .pin_bit_mask = (1ULL << INTERRUPT_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&in_cfg);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(INTERRUPT_PIN, gpio_isr_handler, NULL);
}

/* ---------------- LECTURA ---------------- */
// Retorna la bandera de interrupción

uint8_t interrupt_driver_get_flag(void)
{
    return interrupt_flag;
}

// Retorna el contador de interrupciones

uint32_t interrupt_driver_get_count(void)
{
    return interrupt_count;
}

/* ---------------- ESCRITURA ---------------- */
// Limpia la bandera

void interrupt_driver_clear_flag(void)
{
    interrupt_flag = 0;
}