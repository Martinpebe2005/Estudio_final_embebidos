#include "max7219_service.h"
#include "spi_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Registros principales del MAX7219

#define REG_DECODE_MODE   0x09
#define REG_INTENSITY     0x0A
#define REG_SCAN_LIMIT    0x0B
#define REG_SHUTDOWN      0x0C
#define REG_DISPLAY_TEST  0x0F

/* ---------------- ESCRITURA ---------------- */
// Escribe un registro del MAX7219

void max7219_write(uint8_t reg, uint8_t dato)
{
    spi_driver_write_16(reg, dato);
}

/* ---------------- INICIALIZACIÓN ---------------- */
// Configuración básica del MAX7219

void max7219_init(void)
{
    max7219_write(REG_SHUTDOWN, 0x01);      // Operación normal

    max7219_write(REG_DISPLAY_TEST, 0x01);  // Test ON
    vTaskDelay(pdMS_TO_TICKS(2000));
    max7219_write(REG_DISPLAY_TEST, 0x00);  // Test OFF

    max7219_write(REG_DECODE_MODE, 0xFF);   // Code B en todos los dígitos
    max7219_write(REG_SCAN_LIMIT, 0x03);    // Usa 4 dígitos
    max7219_write(REG_INTENSITY, 0x08);     // Brillo medio
}

/* ---------------- CONVERSIONES ---------------- */
// Convierte un número de 0 a 9999 en 4 dígitos

void max7219_show_number_4digits(uint16_t number)
{
    uint8_t unidades;
    uint8_t decenas;
    uint8_t centenas;
    uint8_t miles;

    unidades = number % 10;
    decenas  = (number / 10) % 10;
    centenas = (number / 100) % 10;
    miles    = (number / 1000) % 10;

    max7219_write(0x01, unidades);
    max7219_write(0x02, decenas);
    max7219_write(0x03, centenas);
    max7219_write(0x04, miles);
}