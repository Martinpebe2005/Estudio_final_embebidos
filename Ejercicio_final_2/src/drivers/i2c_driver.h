#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "esp_err.h"

/* ---------------- INICIALIZACIÓN ---------------- */

void i2c_driver_init(void);

/* ---------------- ESCRITURA ---------------- */

esp_err_t i2c_driver_write_bytes(uint8_t device_addr,
                                 uint8_t reg_addr,
                                 uint8_t *data,
                                 uint8_t len);

/* ---------------- LECTURA ---------------- */

esp_err_t i2c_driver_read_bytes(uint8_t device_addr,
                                uint8_t reg_addr,
                                uint8_t *data,
                                uint8_t len);

#endif