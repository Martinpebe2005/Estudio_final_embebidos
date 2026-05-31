#include "pwm_service.h"
#include "pwm_driver.h"

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el driver PWM

void pwm_service_init(void)
{
    pwm_init();
}

/* ---------------- ESCRITURA ---------------- */
// Envía el porcentaje al driver

void pwm_service_set_percent(int porcentaje)
{
    if (porcentaje < 0) {
        porcentaje = 0;
    }

    if (porcentaje > 100) {
        porcentaje = 100;
    }

    pwm_set(porcentaje);
}