#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//librerias de drivers

#include "i2c_driver.h"

//librerias de servicios

#include "bme280_service.h"




void app_main() {

    i2c_driver_init();

    while(1)
    {
        bme280_Leer_datos();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}