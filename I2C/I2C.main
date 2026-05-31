#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c_driver.h"
#include "ds1307_service.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define READ_DELAY_MS 1000

/* ---------------- LOOP PRINCIPAL ---------------- */

void app_main(void)
{
    i2c_driver_init();

    ds1307_escribir_hora();

    while(1)
    {
        ds1307_leer_hora();

        vTaskDelay(pdMS_TO_TICKS(READ_DELAY_MS));
    }
}