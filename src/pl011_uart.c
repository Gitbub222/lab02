#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"

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

    /*set gpio function*/
    selector = get32(GPFSEL1);
    selector = selector & (~(7<<12));   // clean gpio14
    selector = selector | (4<<12);      // set alt1 for gpio14 
    selector = selector & (~(7<<15));   // clean gpio15
    selector = selector | (4<<15);      // set alt1 for gpio15
    put32(GPFSEL1, selector);

    /*set gpio pull-up/down*/
    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1<<14 | 1<<15));
    delay(150);
    put32(GPPUDCLK0, 0);

	put32(UARTCR, 0);                      // disable uart

	// Set the baud rate
	// 48MHz UART clock; baud rate 115200:
	// Baud rate divisor = 
	// UART clock / (16 * Baud rate) = 48,000,000 / (16 * 115200) = 26.0416667
	// Fractional part = round(0.0416667 * 64) = 3
	put32(UARTIBRD, 26); // Integer part
	put32(UARTFBRD, 3);	 // Fractional part

	// Configure the UART line control register
	// Word length (8 bits), enable FIFOs
	put32(UARTLCR_H, (1<<4) | (3<<5));

	// Enable the UART; enable transmit and receive
	put32(UARTCR, (1 | (3<<8)));
}
