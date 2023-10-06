#ifndef	_P_PL011_UART_H
#define	_P_PL011_UART_H

#include "peripherals/base.h"


//USE https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers

// define UART registers here
#define UARTDR   (PBASE+0x000)  // Data Register
#define UARTFR   (PBASE+0x018)  // Flag Register
#define UARTIBRD (PBASE+0x024)  // Integer Baud Rate Register
#define UARTFBRD (PBASE+0x028)  // Fractional Baud Rate Register
#define UARTLCR_H (PBASE+0x02C)  // Line Control Register
#define UARTCR   (PBASE+0x030)  // Control Register
#define UARTIMSC (PBASE+0x038)  // Interrupt Mask Set/Clear Register
#define UARTICR  (PBASE+0x044)  // Interrupt Clear Register


#endif  /*_P_PL011_UART_H */