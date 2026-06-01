#include "timer_service.h"
#include "timer_driver.h"

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el driver del timer
void timer_service_init(void)
{
    timer_driver_init();
}

/* ---------------- LECTURA ---------------- */
// Compara el tiempo actual contra el último tiempo guardado
uint8_t timer_service_has_elapsed(uint64_t *last, uint64_t period_us)
{
    uint64_t now = timer_driver_get_time_us();

    if (now - *last >= period_us) {
        *last = now;
        return 1;
    }

    return 0;
}