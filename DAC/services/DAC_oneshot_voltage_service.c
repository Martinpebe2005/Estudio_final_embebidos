#include "dac_voltage_service.h"
#include "drivers/dac_oneshot_driver/dac_oneshot_driver.h"

/* ---------------- CONVERSIONES ---------------- */
// Convierte voltaje de 0.0V a 3.3V en valor de 0 a 255
void dac_set_voltage(float voltios)
{
    uint8_t valor = (uint8_t)(voltios * 255.0f / 3.3f);
    dac_oneshot_write(valor);
}