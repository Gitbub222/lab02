#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"

void uart_send(char c)
{
	// implement send function here for pl011

	// Write UART Data Register
	put32(UARTDR, c);
}

char uart_recv(void)
{
	// implement receive function here for pl011

	// Read and return UART Data Register
	return (get32(UARTDR) & 0xFF);
}

void uart_send_string(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		uart_send((char)str[i]);
	}
}

void uart_init(void)
{
	// implement init function here for pl011
	unsigned int selector;

	double base_uart_clock = 48000000;
	double baud_rate = 115200;
	double baud_rate_divisor = base_uart_clock / (16 * baud_rate);
	int integer_baud_rate_divisor = (int)baud_rate_divisor;
	double fraction_part = baud_rate_divisor - integer_baud_rate_divisor;
	int fractional_baud_rate_divisor = ((fraction_part * 64) + 0.5);

	// Disable the UART
	put32(UARTCR, 0x0);

	// Set the baud rate divisor in the UARTIBRD register
	put32(UARTIBRD, integer_baud_rate_divisor);

	// Set the baud rate fraction in the UARTFBRD register
	put32(UARTFBRD, fractional_baud_rate_divisor);

	// Enable the UART
	put32(UARTCR, 0x1);
}
