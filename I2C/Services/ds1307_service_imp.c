#include "ds1307_service.h"

#include "i2c_driver.h"
#include "esp_log.h"

/* ---------------- CONFIGURACIÓN ---------------- */

#define DS1307_ADDR 0x68

#define DS1307_REG_SEC 0x00

/* ---------------- VARIABLES PRIVADAS ---------------- */

static const char *TAG = "DS1307";

/* ---------------- CONVERSIONES ---------------- */

uint8_t decimal_a_bcd(uint8_t decimal)
{
    return ((decimal / 10) << 4) | (decimal % 10);
}

uint8_t bcd_a_decimal(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/* ---------------- ESCRITURA ---------------- */

void ds1307_escribir_hora(void)
{
    uint8_t segundos = 0;
    uint8_t minutos = 30;
    uint8_t horas = 10;

    uint8_t dia = 2;
    uint8_t fecha = 13;
    uint8_t mes = 4;
    uint8_t anio = 26;

    uint8_t datos[7];

    datos[0] = decimal_a_bcd(segundos);
    datos[1] = decimal_a_bcd(minutos);
    datos[2] = decimal_a_bcd(horas);
    datos[3] = decimal_a_bcd(dia);
    datos[4] = decimal_a_bcd(fecha);
    datos[5] = decimal_a_bcd(mes);
    datos[6] = decimal_a_bcd(anio);

    esp_err_t resultado =
        i2c_driver_write_bytes(
            DS1307_ADDR,
            DS1307_REG_SEC,
            datos,
            7);

    if(resultado == ESP_OK)
    {
        ESP_LOGI(TAG,
                 "Hora escrita correctamente");
    }
    else
    {
        ESP_LOGE(TAG,
                 "Error al escribir en el DS1307: %s",
                 esp_err_to_name(resultado));
    }
}

/* ---------------- LECTURA ---------------- */

void ds1307_leer_hora(void)
{
    uint8_t datos[7];

    esp_err_t resultado =
        i2c_driver_read_bytes(
            DS1307_ADDR,
            DS1307_REG_SEC,
            datos,
            7);

    if(resultado != ESP_OK)
    {
        ESP_LOGE(TAG,
                 "Error al leer del DS1307: %s",
                 esp_err_to_name(resultado));

        return;
    }

    uint8_t segundos =
        bcd_a_decimal(datos[0] & 0x7F);

    uint8_t minutos =
        bcd_a_decimal(datos[1] & 0x7F);

    uint8_t horas =
        bcd_a_decimal(datos[2] & 0x3F);

    uint8_t dia =
        bcd_a_decimal(datos[3] & 0x07);

    uint8_t fecha =
        bcd_a_decimal(datos[4] & 0x3F);

    uint8_t mes =
        bcd_a_decimal(datos[5] & 0x1F);

    uint8_t anio =
        bcd_a_decimal(datos[6]);

    ESP_LOGI(
        TAG,
        "Fecha: %02d/%02d/20%02d  Hora: %02d:%02d:%02d  Dia semana: %d",
        fecha,
        mes,
        anio,
        horas,
        minutos,
        segundos,
        dia);
}