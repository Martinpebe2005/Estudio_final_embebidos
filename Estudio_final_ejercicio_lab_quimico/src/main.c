#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//librerias de servicios

#include "bme280_service.h"
#include "MQ150_service.h"

//variables 
static float valor_MQ150 = 0;


void app_main() {

    bme280_service_init();
    MQ150_service_init();

    while(1)
    {
        valor_MQ150 = adc_read_percentage();
        bme280_Leer_datos();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}