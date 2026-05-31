// ─────────────────────────────────────────────────────────────
// EJEMPLO GPIO
// Hace parpadear un LED cada segundo.
// ─────────────────────────────────────────────────────────────

#include "gpio_lib.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ─────────────────────────────────────────────────────────────
// app_main()
// Inicializa GPIO y cambia su estado periódicamente.
// ─────────────────────────────────────────────────────────────

void app_main(void)
{
    gpio_lib_init();

    while (1)
    {
        gpio_lib_toggle();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}