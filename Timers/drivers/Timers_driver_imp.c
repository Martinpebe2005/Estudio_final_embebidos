#include "timer_driver.h"
#include "driver/timer.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Timer usado por el programa
#define TIMER_GROUP_USED TIMER_GROUP_0
#define TIMER_USED       TIMER_0

/* ---------------- INICIALIZACIÓN ---------------- */
// Configura el timer para contar en microsegundos
void timer_driver_init(void)
{
    timer_config_t cfg = {
        .divider     = 80,           // 80MHz / 80 = 1MHz → 1 tick = 1us
        .counter_dir = TIMER_COUNT_UP,
        .counter_en  = TIMER_PAUSE,
        .alarm_en    = TIMER_ALARM_DIS,
        .auto_reload = false,
    };

    timer_init(TIMER_GROUP_USED, TIMER_USED, &cfg);
    timer_set_counter_value(TIMER_GROUP_USED, TIMER_USED, 0);
    timer_start(TIMER_GROUP_USED, TIMER_USED);
}

/* ---------------- LECTURA ---------------- */
// Retorna el contador actual del timer
uint64_t timer_driver_get_time_us(void)
{
    uint64_t now = 0;
    timer_get_counter_value(TIMER_GROUP_USED, TIMER_USED, &now);
    return now;
}