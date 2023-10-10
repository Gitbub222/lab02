#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"
#include <stdint.h>

void uart_send(char c)
{
	// Wait until the UART FIFO is not full
	while (get32(UARTFR) & (1 << 5)); // Wait until TXFF (Transmit FIFO Full) is clear

	// Send the character
	put32(UARTDR, c);
}

char uart_recv(void)
{
	// Wait until the UART FIFO has data
	while (get32(UARTFR) & (1 << 4)); // Wait until RXFE (Receive FIFO Empty) is clear

	// Return the received character
	return (char)(get32(UARTDR) & 0xFF);
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
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7 << 12); // clean gpio14
	selector |= 2 << 12;	// set alt5 for gpio14
	selector &= ~(7 << 15); // clean gpio15
	selector |= 2 << 15;	// set alt5 for gpio15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
	put32(GPPUDCLK0, 0);

	// Mask all interrupts by setting corresponding bits to 1
	put32(UARTIMSC, 0x7ff);

	// Disable DMA by setting all bits to 0
	put32(UARTDMACR, 0);

	// Wait for the end of transmission or reception of the current character
	while (!(get32(UARTFR) & (1 << 7)))
		; // Wait until TXFE (Transmit FIFO Empty) is set
	while (get32(UARTFR) & (1 << 4))
		; // Wait until RXFE (Receive FIFO Empty) is clear

	// Flush the transmit FIFO by setting the FEN bit to 0 in the Line Control Register, UARTLCR_H
	put32(UARTLCR_H, get32(UARTLCR_H) & ~(1 << 4)); // Clear FEN bit
	put32(UARTLCR_H, get32(UARTLCR_H) | (1 << 4));	// Set FEN bit back to enable FIFO

	// Set the baud rate
	// 48MHz UART clock; baud rate 115200:
	// Baud rate divisor = UART clock / (16 * Baud rate) = 48,000,000 / (16 * 115200) = 26.0416667
	// Fractional part = round(0.0416667 * 64) = 3

	// Set the baud rate
	put32(UARTIBRD, 26); // Integer part
	put32(UARTFBRD, 3);	 // Fractional part

	// Configure the UART line control register
	// Word length (8 bits), enable FIFOs
	put32(UARTLCR_H, (3 << 5) | (1 << 4));

	// Enable the UART; enable transmit and receive
	put32(UARTCR, (1 << 0) | (1 << 8) | (1 << 9));
}
