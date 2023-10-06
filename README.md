# lab02    
1.2 Change the OS code to use UART device instead of Mini UART. Use `BCM2837 ARM Peripherals` and [ARM PrimeCell UART (PL011)](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0183g/DDI0183G_uart_pl011_r1p5_trm.pdf) manuals to figure out how to access UART registers and how to configure GPIO pins. The UART device uses the 48MHz clock as a base.


Summary of registers
https://developer.arm.com/documentation/ddi0183/g/programmers-model/summary-of-registers?lang=en


The UART_CR Register is the control register.
 NOTE: 
 To enable transmission, the TXE bit and UARTEN bit must be set to 1. 
 Similarly, to enable reception, the RXE bit and UARTEN bit, must be set to 1. 

 NOTE: Program the control registers as follows: 
 1. Disable the UART. 
 2. Wait for the end of transmission or reception of the current character. 
 3. Flush the transmit FIFO by setting the FEN bit to 0 in the Line Control Register, UART_LCRH. 
 4. Reprogram the Control Register, UART_CR. 5. Enable the UART. 


 Example 3.1 is an example of how to calculate the divisor value.

If the required baud rate is 230400 and UARTCLK = 4MHz then:

Baud Rate Divisor = (4 × 10^6) / (16 × 230400) = 1.085

This means BRDI = 1 and BRDF = 0.085.

Therefore, fractional part, m = integer ( (0.085 × 64) + 0.5 ) = 5

Generated baud rate divider = 1 + 5/64 = 1.078

Generated baud rate = (4 × 10^6) / (16 × 1.078) = 231911


