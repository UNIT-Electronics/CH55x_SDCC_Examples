// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
// Code Rewrite by Master
// -------                                 CH552
//                                       +--\/--+
//                ---------------- P32  1|°     |16  V33 -------------
//                ---------------- P14  2|      |15  Vcc -------------
//                ---------------- P15  3|      |14  GND -------------
//                ---------------- P16  4|      |13  P37 UDM --- USB D-
//                ---------------- P17  5|      |12  P36 UDP --- USB D+
//                ---------------- RST  6|      |11  P34 -------------
//                ---------------- P31  7|      |10  P33 ---------DOUT
//                ---------------- P30  8|      |9   P11 -------------
//                                       +------+

// Libraries

#include "src/config.h"  // pin configurations
#include "src/system.h"   // system functions
#include "src/delay.h"    // delay functions
#include "src/neo.h"      // NeoPixel functions
#include <stdlib.h>       // for random number generation

// ===================================================================================
// NeoPixel Functions
// ===================================================================================




#define delay 100
#define NeoPixel 2 // Number Neopixel conect
#define level 100 // Ilumination level 0 to 255

void randomColorSequence(void) {

  for(int j=0;j<NeoPixel;j++){
      uint8_t red = rand() % level;
      uint8_t green = rand() % level;
      uint8_t blue = rand() % level;
      uint8_t num = rand() % NeoPixel;

      for(int i=0; i<num; i++){
        NEO_writeColor(0, 0, 0);
      }
      NEO_writeColor(red, green, blue);
      DLY_ms(delay);
      NEO_writeColor(0, 0, 0);
    }
    
    for(int l=0; l<9; l++){
        NEO_writeColor(0, 0, 0);
      }

}

void colorSequence(void) {
 
  for(int j=0;j<=NeoPixel;j++){
        uint8_t red = rand() % level;
        uint8_t green = rand() % level;
        uint8_t blue = rand() % level;
      for(int i=0; i<j; i++){
        NEO_writeColor(red, green, blue);
      }
      DLY_ms(delay);
      for(int l=0; l<j; l++){
        NEO_writeColor(0, 0, 0);
      }
  }
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  NEO_init();                       // init NeoPixels
  CLK_config();                     // configure system clock
  DLY_ms(delay);                       // wait for clock to settle

  // Loop
  while (1) {
    randomColorSequence();
    DLY_ms(10);
    colorSequence();
    DLY_ms(10);
  }
}
