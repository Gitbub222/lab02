# lab02
1.1 Introduce a constant `baud_rate`, calculate necessary Mini UART register values using this constant. Make sure that the program can work using baud rates other than 115200.
  
    
1.2 Change the OS code to use UART device instead of Mini UART. Use `BCM2837 ARM Peripherals` and [ARM PrimeCell UART (PL011)](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0183g/DDI0183G_uart_pl011_r1p5_trm.pdf) manuals to figure out how to access UART registers and how to configure GPIO pins. The UART device uses the 48MHz clock as a base.