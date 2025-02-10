#include "src/config.h"
#include "src/system.h"
#include "src/delay.h"
#include "src/neo.h"
#include "src/usb_composite.h"

void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

#pragma disable_warning 110

inline void KEY1_PRESSED() {
  KBD_press(KBD_KEY_UP_ARROW);
  KBD_release(KBD_KEY_UP_ARROW);
}

inline void KEY1_RELEASED() {
}

inline void KEY1_HOLD() {
  MOUSE_wheel_up();
  DLY_ms(10);
}

inline void KEY2_PRESSED() {
  KBD_press(KBD_KEY_DOWN_ARROW);
  KBD_release(KBD_KEY_DOWN_ARROW);
}

inline void KEY2_RELEASED() {
}

inline void KEY2_HOLD() {
  KBD_type(KBD_KEY_DOWN_ARROW);
  DLY_ms(500);
}

inline void KEY3_PRESSED() {
  KBD_print("Unit Electronics");
}

inline void KEY3_RELEASED() {
}

inline void KEY3_HOLD() {
}

void main(void) {
  CLK_config();
  DLY_ms(10);
  PIN_input(PIN_KEY1);
  PIN_input(PIN_KEY2);
  PIN_input(PIN_KEY3);
  HID_init();
  NEO_init();

  while (1) {
    if (PIN_read(PIN_KEY1)) {
      KEY1_PRESSED();
      NEO_writeColor(255, 0, 0);
    } else if (PIN_read(PIN_KEY2)) {
      KEY2_PRESSED();
      NEO_writeColor(0, 255, 0);
    } else if (PIN_read(PIN_KEY3)) {
      KEY3_PRESSED();
      NEO_writeColor(0, 0, 255);
    } else {
      NEO_writeColor(0, 0, 0);
      DLY_ms(40);
    }
  }
}
