// ===================================================================================
// User Configurations for CH552 DAPLink
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_LED             P11       // pin connected to LED, active low
#define PIN_SWD             P15       // pin connected to SWDIO/TMS via 100R resistor
#define PIN_SWK             P16       // pin connected to SWCLK/TCK via 100R resistor
#define PIN_RST             P17       // pin connected to nRESET
#define PIN_TDO             P14       // pin connected to TDO via 100R resistor
#define PIN_TDI             P32       // pin connected to TDI via 100R resistor
#define PIN_TRST            P34       // pin connected to nTRST
#define PIN_RXD             P30       // pin connected to RXD via 470R resistor
#define PIN_TXD             P31       // pin connected to TXT via 470R resistor

#define USB_VENDOR_ID       0x1209    // VID (shared www.voti.nl)
#define USB_PRODUCT_ID      0x27DD    // PID (shared CDC)
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    500       // max power in mA 

// #define UART_BAUD         115200
#define UART_BAUD         9600
#define CDC_BAUD          9600
// USB descriptor strings
#define MANUFACTURER_STR    'U','N','T','e','l','e','c','t','r','o','n','i','c','s'
#define PRODUCT_STR         'I','2','C','-','B','r','i','d','g','e'
#define SERIAL_STR          'g','i','t','h','u','b','.','c','o','m','/', \
                            'U','N','T','e','l','e','c','t','r','o','n','i','c','s'
#define INTERFACE_STR       'M','i','c','r','o','H','o','n','i','t', \
                            'o',' ','r','e','v','0','.','0','.','1'
