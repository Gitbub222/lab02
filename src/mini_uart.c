#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	//implement send function here for pl011
}

char uart_recv ( void )
{
	//implement receive function here for pl011
	
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;

}
