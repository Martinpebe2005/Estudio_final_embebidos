#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "driver/spi_master.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Prototipos del driver SPI

void spi_driver_init(void);
void spi_driver_write_16(uint8_t byte_alto, uint8_t byte_bajo);

#endif