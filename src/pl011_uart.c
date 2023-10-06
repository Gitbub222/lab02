#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"

void uart_send(char c)
{
	// implement send function here for pl011
	while (1)
	{
		if (get32(UARTFR) & (1 << 5))
			break;
	}

	// Write UART Data Register
	put32(UARTDR, c);
}

char uart_recv(void)
{
	// implement wait
	while (1)
	{
		if (get32(UARTFR) & (1 << 4))
			break;
	}

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

	// (A) Configure GPIO pins
	unsigned int selector = get32(GPFSEL1);
	selector &= ~(7 << 12); // clean GPIO14 
	selector |= (4 << 12);	// Set alt0 for GPIO14 (TXD)
	selector &= ~(7 << 15); // clean GPIO15 
	selector |= (4 << 15);	// Set alt0 for GPIO15 (RXD)
	put32(GPFSEL1, selector);

	// Disable pull-up/pull-down control line
	put32(GPPUD, 0);
	delay(150);

	// Disable pull-up/pull-down for pin 14,15
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	put32(GPPUDCLK0, 0);

	unsigned int base_uart_clock = 48000000;
    unsigned int baud_rate = 115200;

    // avoid floating-point arithmetic
    unsigned int baud_rate_divisor = base_uart_clock / (16 * baud_rate);
    unsigned int remainder = base_uart_clock % (16 * baud_rate);
    unsigned int fractional_baud_rate_divisor = (8 * remainder / baud_rate) >> 1;
    if ((remainder % baud_rate) >= (baud_rate / 2)) fractional_baud_rate_divisor++;


	// 1. Disable the UART
	put32(UARTCR, 0);

	// 2. Wait for the end of transmission or reception of the current character
	while (1)
	{
		if (get32(UARTFR) & ~8)
			break;
	}

	// Set the baud rate divisor in the UARTIBRD register
	put32(UARTIBRD, baud_rate_divisor);

	// Set the baud rate fraction in the UARTFBRD register
	put32(UARTFBRD, fractional_baud_rate_divisor);

	// 3. Flush the transmit FIFO by setting the FEN bit to 0 in the Line Control Register, UARTLCR_H.
	put32(UARTLCR_H, get32(UARTLCR_H) & ~16);

	// 4. Reprogram the Control Register, UART_CR
	put32(UARTCR, 1 | 256 | 512);

	// 5. Enable the UART
	put32(UARTCR, get32(UARTCR) | 1);
}
