#include "src/system.h" 
#include "src/gpio.h"   
#include "src/delay.h"  

#define PIN_LED P34
#define PIN_BUTTON P33

void main(void)
{
  CLK_config();
  DLY_ms(5);
  PIN_input(PIN_BUTTON);
  PIN_output(PIN_LED);
  while (1)
  {
    if (PIN_read(PIN_BUTTON)){
      PIN_high(PIN_LED);
    }
    else{
      PIN_low(PIN_LED);
    }
  }
}