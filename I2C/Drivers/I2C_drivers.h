#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "esp_err.h"
#include "driver/i2c.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Funciones públicas para usar el bus I2C

void i2c_driver_init(void);

esp_err_t i2c_driver_write_bytes(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

esp_err_t i2c_driver_read_bytes(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

#endif