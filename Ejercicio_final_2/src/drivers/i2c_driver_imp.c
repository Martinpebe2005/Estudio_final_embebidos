#include "i2c_driver.h"

#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define I2C_SDA_PIN 32
#define I2C_SCL_PIN 33

#define I2C_PORT I2C_NUM_0

#define I2C_FREQ_HZ 100000

/* ---------------- VARIABLES PRIVADAS ---------------- */

static const char *TAG = "I2C_DRIVER";

/* ---------------- INICIALIZACIÓN ---------------- */

void i2c_driver_init(void)
{
    i2c_config_t config = {

        .mode = I2C_MODE_MASTER,

        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,

        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,

        .master.clk_speed = I2C_FREQ_HZ,
    };

    i2c_param_config(I2C_PORT, &config);

    i2c_driver_install(I2C_PORT, config.mode, 0, 0, 0);

    ESP_LOGI(TAG,
             "Bus I2C inicializado SDA=%d SCL=%d",
             I2C_SDA_PIN,
             I2C_SCL_PIN);
}

/* ---------------- ESCRITURA ---------------- */

esp_err_t i2c_driver_write_bytes(uint8_t device_addr,
                                 uint8_t reg_addr,
                                 uint8_t *data,
                                 uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);

    i2c_master_write_byte(
        cmd,
        (device_addr << 1) | I2C_MASTER_WRITE,
        true);

    i2c_master_write_byte(
        cmd,
        reg_addr,
        true);

    i2c_master_write(
        cmd,
        data,
        len,
        true);

    i2c_master_stop(cmd);

    esp_err_t resultado =
        i2c_master_cmd_begin(
            I2C_PORT,
            cmd,
            pdMS_TO_TICKS(1000));

    i2c_cmd_link_delete(cmd);

    return resultado;
}

/* ---------------- LECTURA ---------------- */

esp_err_t i2c_driver_read_bytes(uint8_t device_addr,
                                uint8_t reg_addr,
                                uint8_t *data,
                                uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);

    i2c_master_write_byte(
        cmd,
        (device_addr << 1) | I2C_MASTER_WRITE,
        true);

    i2c_master_write_byte(
        cmd,
        reg_addr,
        true);

    i2c_master_start(cmd);

    i2c_master_write_byte(
        cmd,
        (device_addr << 1) | I2C_MASTER_READ,
        true);

    i2c_master_read(
        cmd,
        data,
        len - 1,
        I2C_MASTER_ACK);

    i2c_master_read_byte(
        cmd,
        &data[len - 1],
        I2C_MASTER_NACK);

    i2c_master_stop(cmd);

    esp_err_t resultado =
        i2c_master_cmd_begin(
            I2C_PORT,
            cmd,
            pdMS_TO_TICKS(1000));

    i2c_cmd_link_delete(cmd);

    return resultado;
}