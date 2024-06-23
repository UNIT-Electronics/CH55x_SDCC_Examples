// ===================================================================================
// Project:   USB CDC Passthrough for CH551, CH552, CH554
// Version:   v1.0
// Year:      2024
// Author:    Adrian Rabadan Ortiz
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// This code implements a simple USB passthrough for CH551, CH552, and CH554.
// The CH55x builds a USB communication device class (CDC) for serial communication
// via USB. Data received via USB will be sent back to the host.
//
// Wiring:
// -------
// Connect the board via USB to your PC. It should be detected as a CDC device.
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: 16 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash' immediatly afterwards.
// - To compile the firmware using the Arduino IDE, follow the instructions in the 
//   .ino file.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include "src/config.h"                   // user configurations
#include "src/system.h"                   // system functions
#include "src/gpio.h"                     // for GPIO
#include "src/delay.h"                    // for delays
#include "src/usb_cdc.h"                  // for USB-CDC serial

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Main Function
// ===================================================================================

void main(void) {
  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to stabilize
  CDC_init();                             // init USB CDC

  // Loop
  while(1) {
    if(CDC_available()) {                 // something coming in?
      char c = CDC_read();                // read the character ...
      CDC_writeflush(c);                  // ... and send it back
    }
  }
}
