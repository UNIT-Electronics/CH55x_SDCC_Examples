// ===================================================================================
// User configurations
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_BUZZER          P15       // buzzer pin
#define PIN_SDA             P31       // I2C SDA
#define PIN_SCL             P30       // I2C SCL
#define PIN_PWM             P34       // PWM pin


// USB device descriptor
#define USB_VENDOR_ID       0x1209    // VID (open source hardware projects)
#define USB_PRODUCT_ID      0x27DD    // PID (shared CDC)
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    100       // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'U','n','i','t','-','E','l','e','c','t','r','o','n','i','c','s'
#define PRODUCT_STR         'U','S','B','_','C','D','C','-','S','e','r','i','a','l'
#define SERIAL_STR          'g','i','t','h','u','b','.','c','o','m','/', \
                            'U','n','i','t','-','E','l','e','c','t','r','o','n','i','c','s'
#define INTERFACE_STR       'C','D','C',' ','S','e','r','i','a','l'
