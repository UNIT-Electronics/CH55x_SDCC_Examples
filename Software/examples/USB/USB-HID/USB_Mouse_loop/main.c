// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include "src/system.h"                   // system functions
#include "src/neo.h"                      // NeoPixel functions
#include "src/usb_mouse.h"                // USB HID mouse functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Precomputed Values for Infinity Shape
// ===================================================================================
#define INFINITY_POINTS 32                // Number of points around the infinity shape
#define INFINITY_WIDTH  15                // Width of the infinity shape
#define INFINITY_HEIGHT 10                // Height of the infinity shape

// Precomputed X and Y positions for the infinity shape (32 points)
const int8_t infinity_x[INFINITY_POINTS] = {
  15,  12,   8,   4,   0,  -4,  -8, -12, -15, -12,  -8,  -4,   0,   4,   8,  12,
  15,  12,   8,   4,   0,  -4,  -8, -12, -15, -12,  -8,  -4,   0,   4,   8,  12
};
const int8_t infinity_y[INFINITY_POINTS] = {
   0,   5,   8,  10,  10,   8,   5,   0,  -5,  -8, -10, -10,  -8,  -5,   0,   5,
   0,  -5,  -8, -10, -10,  -8,  -5,   0,   5,   8,  10,  10,   8,   5,   0,  -5
};

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Variables
  uint8_t hue = 0;                        // hue cycle value
  uint8_t point_index = 0;                // index for the infinity shape points

  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(10);                             // wait for clock to settle
  MOUSE_init();                           // init USB HID mouse
  DLY_ms(500);                            // wait for Windows
  NEO_init();                             // init NeoPixel
  WDT_start();                            // start watchdog

  // Loop
  while(1) {
    // NeoPixel color update
    NEO_writeHue(hue, 0);                 // set NeoPixel hue value
    if(!hue--) hue = 191;                 // cycle hue value

    // Move the mouse along the infinity path
    MOUSE_move(infinity_x[point_index], infinity_y[point_index]); 

    // Move to the next point in the infinity shape
    point_index++;
    if (point_index >= INFINITY_POINTS) {
      point_index = 0;                    // reset to start of infinity path
    }

    // Delay and reset watchdog
    DLY_ms(50);                           // delay a little, also NeoPixel latch
    WDT_reset();                          // reset watchdog
  }
}
