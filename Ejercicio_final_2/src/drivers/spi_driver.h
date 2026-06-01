#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include "driver/spi_master.h"

/* ---------------- INICIALIZACIÓN ---------------- */

void spi_driver_init(void);

/* ---------------- ESCRITURA ---------------- */

void spi_driver_write_8(uint8_t data);
void spi_driver_write_16(uint8_t byte_alto, uint8_t byte_bajo);

/* ---------------- LECTURA ---------------- */

uint8_t spi_driver_read_8(void);

/* ---------------- TRANSFERENCIA ---------------- */

uint8_t spi_driver_transfer_8(uint8_t data);

#endif