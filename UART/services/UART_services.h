#ifndef UART_SERVICE_H
#define UART_SERVICE_H

void uart_service_send_values(float valor1, float valor2);
float uart_service_receive_cmd(void);

#endif