#ifndef INTERRUPT_SERVICE_H
#define INTERRUPT_SERVICE_H

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el servicio
void interrupt_service_init(void);

/* ---------------- LOOP PRINCIPAL ---------------- */
// Procesa la interrupción
void interrupt_service_update(void);

#endif