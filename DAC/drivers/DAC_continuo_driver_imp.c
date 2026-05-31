#include "dac_continuous_driver.h"
#include "driver/dac_continuous.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// DAC_CH0 = GPIO25, DAC_CH1 = GPIO26
#define DAC_FREQ_HZ 10000

/* ---------------- VARIABLES PRIVADAS ---------------- */
// Handle del DAC continuo
static dac_continuous_handle_t dac_handle;

/* ---------------- INICIALIZACIÓN ---------------- */
// Configura el DAC continuo
void dac_continuo_init(void)
{
    dac_continuous_config_t cfg = {
        .chan_mask  = DAC_CHANNEL_MASK_CH0,
        .desc_num   = 4,
        .buf_size   = 256,
        .freq_hz    = DAC_FREQ_HZ,
        .offset     = 0,
        .clk_src    = DAC_DIGI_CLK_SRC_DEFAULT,
        .chan_mode  = DAC_CHANNEL_MODE_ALTER,
    };

    dac_continuous_new_channels(&cfg, &dac_handle);
    dac_continuous_enable(dac_handle);
}

/* ---------------- ESCRITURA ---------------- */
// Envía una tabla al DAC para repetirse cíclicamente
void dac_continuo_write_table(uint8_t *tabla, uint32_t size)
{
    dac_continuous_write_cyclically(dac_handle, tabla, size, NULL);
}