#include "waveform_service.h"
#include <math.h>

/* ---------------- VARIABLES PRIVADAS ---------------- */
// Tablas de muestras para el DAC
static uint8_t tabla_seno[NUM_SAMPLES];
static uint8_t tabla_sierra[NUM_SAMPLES];

/* ---------------- INICIALIZACIÓN ---------------- */
// Genera las tablas seno y sierra
void waveform_service_init(float amplitud, float offset_v)
{
    uint8_t centro = (uint8_t)(offset_v * 255.0f / 3.3f);
    uint8_t amp    = (uint8_t)(amplitud * 127.5f);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        tabla_seno[i] = (uint8_t)(centro + amp * sin(2.0 * M_PI * i / NUM_SAMPLES));
        tabla_sierra[i] = (uint8_t)((centro - amp) + (2 * amp * i / (NUM_SAMPLES - 1)));
    }
}

/* ---------------- LECTURA ---------------- */
// Entrega la tabla seno
uint8_t *waveform_get_sine_table(void)
{
    return tabla_seno;
}

/* ---------------- LECTURA ---------------- */
// Entrega la tabla sierra
uint8_t *waveform_get_saw_table(void)
{
    return tabla_sierra;
}