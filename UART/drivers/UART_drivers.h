#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "driver/uart.h"

#define UART_PORT UART_NUM_0
#define UART_BUF_SIZE 1024

void uart_driver_init(void);
void uart_driver_send_string(const char *msg);
void uart_driver_send_values(float valor1, float valor2);
int uart_driver_read_line(char *buffer, int max_len);

#endif