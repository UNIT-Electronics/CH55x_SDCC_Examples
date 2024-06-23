// ===================================================================================
// Project:   USB CDC PWM Controller for CH551, CH552, CH554
// Version:   v1.0
// Year:      2024
// Author:    Adrian Rabadan Ortiz
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// This code implements a USB CDC controlled PWM for CH551, CH552, and CH554.
// The CH55x builds a USB communication device class (CDC) for serial communication
// via USB. Data received via USB will be used to set the PWM value (0-255).
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
#include <stdio.h>
#include <stdlib.h>                      // for atoi
#include <string.h>                      // for memset
#include "src/config.h"                  // user configurations
#include "src/system.h"                  // system functions
#include "src/gpio.h"                    // for GPIO
#include "src/delay.h"                   // for delays
#include "src/usb_cdc.h"                 // for USB-CDC serial
#include "src/pwm.h"                     // for PWM

// Define PWM pin
#define PIN_PWM P34

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// Function to change PWM value
void change_pwm(int value) {
  PWM_write(PIN_PWM, value);
}

// ===================================================================================
// Main Function
// ===================================================================================

void main(void) {
  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to stabilize
  CDC_init();                             // init USB CDC
  PWM_set_freq(1);                        // set PWM frequency
  PIN_output(PIN_PWM);                    // set PWM pin as output
  PWM_start(PIN_PWM);                     // start PWM
  PWM_write(PIN_PWM, 0);                  // initialize PWM with 0

  // Buffer to store received data
  char buffer[5] = {0};               

  // Loop
  while(1) {
    // Wait until there is data available in the USB buffer
    if(CDC_available()) {
      // Reset buffer
      memset(buffer, 0, sizeof(buffer));
      
      // Read data from USB
      for(int i = 0; i < 4 && CDC_available(); i++) {
        buffer[i] = CDC_read();
      }

      // Convert buffer to integer
      int value = atoi(buffer);
      // Check if value is within the valid range
      if(value >= 0 && value <= 255) {
        change_pwm(value);                // change PWM value
        CDC_print("PWM updated to: ");
        CDC_println(buffer);              // print confirmation message
      } else {
        CDC_println("Error: Value out of range (0-255)");
      }
    }
  }
}





