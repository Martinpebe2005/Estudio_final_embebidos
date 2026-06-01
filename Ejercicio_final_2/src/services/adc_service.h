#ifndef ADC_SERVICE_H
#define ADC_SERVICE_H

/* ---------------- INICIALIZACIÓN ---------------- */

// Inicializa el servicio ADC
void MQ135_service_init(void);


// Conversión a porcentaje
float MQ135_read_percentage(void);

#endif