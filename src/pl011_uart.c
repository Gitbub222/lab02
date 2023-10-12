#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"
#include <stdint.h>

void uart_send(char ch)
{
    /*Transmit FIFO is full*/
    while (get32(UARTFR) & (1<<5))
    {
        ;
    }
    put32(UARTDR, ch);
}

char uart_recv(void)
{
    /*Receive FIFO is empty*/
    while (get32(UARTFR) & (1<<4))
    {
        ;
    }
    return (get32(UARTDR) & 0xFF);
}

void uart_send_string(char* str)
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


    /*Initializing PL011 uart*/
    put32(UARTCR, 0);                      // disable uart
    put32(UARTIBRD, 26);                   // set baudrate = 115200
    put32(UARTFBRD, 3);
    put32(UARTLCR_H, (1<<4) | (3<<5));      // 8bits and enable FIFO
    put32(UARTCR, (1 | (3<<8)));           // enable uart, rx, tx
}