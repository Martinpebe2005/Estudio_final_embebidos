#include "uart_service.h"
#include "uart_driver.h"
#include <stdio.h>

/* ---------------- CONFIGURACIÓN ---------------- */
// Tamaño del buffer para mensajes

#define MSG_SIZE 64

/* ---------------- ESCRITURA ---------------- */
// Formatea y envía datos por UART

void uart_service_send_values(float valor1, float valor2)
{
    char msg[MSG_SIZE];

    sprintf(msg, "V1:%.1f V2:%.1f\n", valor1, valor2);

    uart_driver_send_string(msg);
}

/* ---------------- LECTURA ---------------- */


float uart_service_receive_cmd(void)
{
    char buffer[UART_BUF_SIZE];

    int len = uart_driver_read_line(buffer, UART_BUF_SIZE);

    if (len > 0) {
        if (strcmp(buffer, "STATUS") == 0) {
            return 1;
        }
    }

    return -1;
}