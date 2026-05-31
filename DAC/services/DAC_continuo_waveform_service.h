#ifndef WAVEFORM_SERVICE_H
#define WAVEFORM_SERVICE_H

#include <stdint.h>

/* ---------------- CONFIGURACIÓN ---------------- */
// Número de muestras de la tabla
#define NUM_SAMPLES 256

/* ---------------- INICIALIZACIÓN ---------------- */
// Crea las tablas de señal
void waveform_service_init(float amplitud, float offset_v);

/* ---------------- LECTURA ---------------- */
// Retorna la tabla seno
uint8_t *waveform_get_sine_table(void);

/* ---------------- LECTURA ---------------- */
// Retorna la tabla sierra
uint8_t *waveform_get_saw_table(void);

#endif