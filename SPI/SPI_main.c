#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "spi_driver.h"
#include "max7219_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Valor de prueba para mostrar

#define TEST_NUMBER 1234

/* ---------------- LOOP PRINCIPAL ---------------- */
// Aplicación principal

void app_main(void)
{
    spi_driver_init();
    max7219_init();

    max7219_show_number_4digits(TEST_NUMBER);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}