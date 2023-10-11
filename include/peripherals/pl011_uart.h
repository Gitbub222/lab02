#ifndef _P_PL011_UART_H
#define _P_PL011_UART_H

#include "peripherals/base.h"


//USE https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers

// define UART registers here
#define UARTDR (PBASE + 0x201000)    // Data Register (writing to this register initiates the actual data transmission)
#define UARTFR (PBASE + 0x201018)    // Flag Register (reading this register we can check if transmission is complete)
#define UARTIBRD (PBASE + 0x201024)  // Integer Baud Rate Register  (responsible for the speed)
#define UARTFBRD (PBASE + 0x201028)  // Fractional Baud Rate Register (responsible for the speed)
#define UARTLCR_H (PBASE + 0x20102C) // Line Control Register (controls the data frame format.)
#define UARTCR (PBASE + 0x201030)    // Control Register (we can enable/disable UART)
#define UARTIMSC (PBASE + 0x201038)  // Interrupt Mask Set/Clear Register (allows to mask(enable./disable) interrupts)
#define UARTICR (PBASE + 0x201044)   // Interrupt Clear Register
#define UARTDMACR (PBASE + 0x201048) // controls DMA

#endif /*_P_PL011_UART_H */
