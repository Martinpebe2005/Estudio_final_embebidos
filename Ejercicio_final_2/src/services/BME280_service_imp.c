#include "bme280_service.h"

#include "i2c_driver.h"
#include "esp_log.h"

//direcciones del BME280

#define BME280_ADDR 0x76
#define BME280_REG_MSB_PRESSURE 0xFA

//variable privada para el tag de log

static const char *TAG = "BME280";

//inicializo el i2c

void bme280_service_init(void){
    i2c_driver_init();
}

//Funcion de lectura de los datos del sensor

void bme280_Leer_datos(void){

    uint8_t data[3];

    esp_err_t ret = i2c_driver_read_bytes(
        BME280_ADDR,
        BME280_REG_MSB_PRESSURE,
        data,
        sizeof(data)
        );

    if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Error leyendo BME280");
            return;
        }
    
    //leemos los datos de los registros

    uint32_t temperature_raw =
        ((uint32_t)data[0] << 12) |
        ((uint32_t)data[1] << 4)  |
        ((uint32_t)data[2] >> 4);


    float temperature = float(temperature_raw);


    ESP_LOGI(TAG, "Temperatura RAW: %lu", temperature_raw);
    ESP_LOGI(TAG, "Presion RAW:     %lu", pressure_raw);
    ESP_LOGI(TAG, "Humedad RAW:     %lu", humidity_raw);
}
