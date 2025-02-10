// ===================================================================================
// User Configurations for CH552G USB ADC KEYBOARD 
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_NEO             P33         // pin connected to NeoPixel
#define PIN_KEY1            P30         // pin connected to key 1
#define PIN_KEY2            P31         // pin connected to key 2
#define PIN_KEY3            P11         // pin connected to key 3



#define PIN_PWM             P34         // pin connected to PWM output
#define PIN_ADC             P32         // pin connected to ADC input
// NeoPixel configuration
#define NEO_COUNT           1          // number of pixels in the string


#define NEO_GRB                         // type of pixel: NEO_GRB or NEO_RGB

// USB device descriptor
#define USB_VENDOR_ID       0x1189      // VID
#define USB_PRODUCT_ID      0x8890      // PID
#define USB_DEVICE_VERSION  0x0100      // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    150         // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'g','e','n','e','r','i','c','d','e','v','i','c','e'
#define PRODUCT_STR         'H','I','D',' ','K','e','y','b','o','a','r','d'
#define SERIAL_STR          'C','H','5','5','2','x','H','I','D'
#define INTERFACE_STR       'H','I','D','-','K','e','y','b','o','a','r','d'
