#include "pwm_driver.h"
#include "driver/ledc.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Cambia este pin, frecuencia y resolución según el montaje

#define PWM_PIN 4 // reemplaza por tu pin

/* ---------------- INICIALIZACIÓN ---------------- */
// Configura el timer y el canal PWM

void pwm_init(void)
{
    // 1. timer: define frecuencia y resolución
    ledc_timer_config_t timer = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .timer_num       = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_12_BIT, // 0-4095
        .freq_hz         = 5000,              // reemplaza según necesidad
        .clk_cfg         = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&timer);

    // 2. canal: vincula timer con pin
    ledc_channel_config_t channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .timer_sel  = LEDC_TIMER_0,
        .intr_type  = LEDC_INTR_DISABLE,
        .gpio_num   = PWM_PIN,
        .duty       = 0,
        .hpoint     = 0,
    };
    ledc_channel_config(&channel);
}

/* ---------------- ESCRITURA ---------------- */
// Recibe porcentaje 0-100 y lo convierte a duty de 12 bits

void pwm_set(int porcentaje)
{
    int duty = (porcentaje * 4095) / 100;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}