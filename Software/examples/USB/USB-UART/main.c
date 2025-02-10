// ===================================================================================
// Project:   USB-UART (CH552) Virtual COM Port
// Version:   v1.0
// Year:      2024
// Author:    Cesar Bautista
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------

// This example demonstrates how to create a virtual COM port and a UART port. 
// The virtual COM port is created using the USB CDC protocol, while the UART port 
// is created using the UART0 module. 
//
// References:
// -----------
// - CH552-DAPLink: https://github.com/wagiminator/CH552-DAPLink/tree/main
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
// - ARMmbed DAPLink: https://github.com/ARMmbed/DAPLink
// - picoDAP: https://github.com/wagiminator/CH552-picoDAP
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH552
// - Clock: 24 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.

//


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include "src/system.h"                     // system functions
#include "src/delay.h"                      // delay functions
#include "src/usb_cdc.h"                    // USB CDC functions
#include "src/uart.h"                       // UART functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

void UART_interrupt(void);
void UART_ISR(void) __interrupt(INT_NO_UART0) {
  UART_interrupt();
}

 
// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Setup
  CLK_config();                             // configure system clock
  DLY_ms(10);                               // wait for clock to settle
  UART_init();                              // init UART
  CDC_init();                               // init virtual COM

  // Loop
  while(1) {
  

    // Handle virtual COM
    if(CDC_available() && UART_ready()) UART_write(CDC_read());
    if(UART_available() && CDC_getDTR()) {
      while(UART_available()) CDC_write(UART_read());
      CDC_flush();
    }
  }
}
