#include "interrupt_service.h"
#include "interrupt_driver.h"

#include <stdio.h>

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el driver

void interrupt_service_init(void)
{
    interrupt_driver_init();
}

/* ---------------- LOOP PRINCIPAL ---------------- */
// Atiende eventos generados por la interrupción

void interrupt_service_update(void)
{
    if (interrupt_driver_get_flag())
    {
        interrupt_driver_clear_flag();

        printf("Interrupcion detectada\n");
        printf("Conteo: %lu\n", interrupt_driver_get_count());
    }
}