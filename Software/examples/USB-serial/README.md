# USB CDC Serial for CH55x

## USB Passthrough for CH55x Microcontrollers

This project implements a simple USB passthrough functionality using CH551, CH552, or CH554 microcontrollers. The microcontroller acts as a USB Communication Device Class (CDC), enabling serial communication over USB. Data received via USB is immediately sent back to the host computer.
Wiring

Connect the CH55x development board to your PC via USB. It should be automatically detected as a CDC device.
Compilation Instructions

    Chip: CH551, CH552, or CH554
    Clock: 16 MHz internal
    Adjust firmware parameters in src/config.h if necessary.
    Ensure SDCC toolchain and Python3 with PyUSB are installed.
    Press the BOOT button on the board and keep it pressed while connecting it via USB to your PC.
    Run make flash immediately afterwards to flash the firmware.
    For compilation using Arduino IDE, refer to instructions in the .ino file.


## USB CDC PWM Controller for CH55x Microcontrollers

This project implements a USB CDC controlled PWM functionality using CH551, CH552, or CH554 microcontrollers. The microcontroller acts as a USB Communication Device Class (CDC), allowing serial communication over USB. Data received via USB is used to set the PWM value (0-255).
Wiring

Connect the CH55x development board to your PC via USB. It should be automatically detected as a CDC device.
Compilation Instructions

    Chip: CH551, CH552, or CH554
    Clock: 16 MHz internal
    Adjust firmware parameters in src/config.h if necessary.
    Ensure SDCC toolchain and Python3 with PyUSB are installed.
    Press the BOOT button on the board and keep it pressed while connecting it via USB to your PC.
    Run make flash immediately afterwards to flash the firmware.
    For compilation using Arduino IDE, refer to instructions in the .ino file.



## Linux Configuration for USB CDC Devices

To configure permissions for USB CDC devices (/dev/ttyACM0), follow these steps:

    Create a new udev rule file:

    ```bash

sudo nano /etc/udev/rules.d/99-custom-usb.rules
```

Add the following rule to the file (replace idVendor and idProduct with your device's actual IDs):

```bash

SUBSYSTEM=="tty", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="27dd", GROUP="dialout", MODE="0666"
```

Save the file (Ctrl + O in nano, then Enter) and exit nano (Ctrl + X).

Reload udev rules for changes to take effect:

``` bash

    sudo udevadm control --reload-rules
```
Example Commands for Serial Communication

    Send data to USB device:

  ``` bash

echo -e 'Hello World!\n' > /dev/ttyACM0
```

Read data from USB device:

``` bash

    cat /dev/ttyACM0
```
These commands allow you to interact with USB CDC devices connected to your Linux system. Adjust the device path (/dev/ttyACM0) as per your setup.

