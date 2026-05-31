#include "bme280_service.h"

#include "i2c_driver.h"
#include "esp_log.h"

//direcciones del BME280

#define BME280_ADDR 0x76
#define BME280_REG_MSB_PRESSURE 0xF7

//variable privada para el tag de log

static const char *TAG = "BME280";

//Funcion de lectura de los datos del sensor

void bme280_Leer_datos(void){

    uint8_t data[8];

    esp_err_t ret = i2c_driver_read_bytes(
        BME280_ADDR,
        BME280_REG_MSB_PRESSURE,
        data,
        8
        );

    if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Error leyendo BME280");
            return;
        }
    
    //leemos los datos de los registros

    uint32_t pressure_raw =
        ((uint32_t)data[0] << 12) |
        ((uint32_t)data[1] << 4)  |
        ((uint32_t)data[2] >> 4);

    uint32_t temperature_raw =
        ((uint32_t)data[3] << 12) |
        ((uint32_t)data[4] << 4)  |
        ((uint32_t)data[5] >> 4);

    uint32_t humidity_raw =
        ((uint32_t)data[6] << 8) |
        data[7];

    float pressure = float(pressure_raw);
    float temperature = float(temperature_raw);
    float humidity = float(humidity_raw);

    ESP_LOGI(TAG, "Temperatura RAW: %lu", temperature_raw);
    ESP_LOGI(TAG, "Presion RAW:     %lu", pressure_raw);
    ESP_LOGI(TAG, "Humedad RAW:     %lu", humidity_raw);
}
