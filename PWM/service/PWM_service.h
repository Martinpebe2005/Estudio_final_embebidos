#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el servicio PWM

void pwm_service_init(void);

/* ---------------- ESCRITURA ---------------- */
// Cambia el porcentaje del PWM

void pwm_service_set_percent(int porcentaje);

#endif