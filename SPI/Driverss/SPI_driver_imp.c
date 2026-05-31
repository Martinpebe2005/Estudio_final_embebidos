#include "spi_driver.h"

/* ---------------- CONFIGURACIÓN ---------------- */
// Pines usados para SPI

#define PIN_MOSI  32
#define PIN_CLK   25
#define PIN_CS    33

/* ---------------- VARIABLES PRIVADAS ---------------- */
// Handle del dispositivo SPI

static spi_device_handle_t spi_device;

/* ---------------- INICIALIZACIÓN ---------------- */
// Inicializa el bus SPI y agrega el dispositivo

void spi_driver_init(void)
{
    spi_bus_config_t bus = {
        .mosi_io_num   = PIN_MOSI,
        .miso_io_num   = -1,
        .sclk_io_num   = PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_CH_AUTO);

    spi_device_interface_config_t dev = {
        .clock_speed_hz = 1000000,
        .mode           = 0,
        .spics_io_num   = PIN_CS,
        .queue_size     = 1,
    };

    spi_bus_add_device(SPI2_HOST, &dev, &spi_device);
}

/* ---------------- ESCRITURA ---------------- */
// Envía dos bytes por SPI

void spi_driver_write_16(uint8_t byte_alto, uint8_t byte_bajo)
{
    uint8_t buf[2];

    buf[0] = byte_alto;
    buf[1] = byte_bajo;

    spi_transaction_t t = {
        .length    = 16,
        .tx_buffer = buf,
    };

    spi_device_transmit(spi_device, &t);
}