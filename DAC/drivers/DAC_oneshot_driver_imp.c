#include "dac_oneshot_driver.h"
#include "driver/dac_oneshot.h"

/* ---------------- VARIABLES PRIVADAS ---------------- */
// Handle del DAC one-shot
static dac_oneshot_handle_t dac_handle;

/* ---------------- INICIALIZACIÓN ---------------- */
// Configura el DAC en GPIO25
void dac_oneshot_init(void)
{
    dac_oneshot_config_t cfg = {
        .chan_id = DAC_CHAN_0,
    };

    dac_oneshot_new_channel(&cfg, &dac_handle);
}

/* ---------------- ESCRITURA ---------------- */
// Envía un valor digital al DAC
void dac_oneshot_write(uint8_t valor)
{
    dac_oneshot_output_voltage(dac_handle, valor);
}