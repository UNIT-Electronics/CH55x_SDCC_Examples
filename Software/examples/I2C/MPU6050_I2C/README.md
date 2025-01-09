# MPU6050 Module I2C Example 

This example demonstrates how to use the I2C interface to read data from the MPU6050 sensor.


## Hardware Required

- Cocket Nova development board 
- MPU6050 sensor


## Compile and Run

This example uses the `I2C Bit Banging` library to communicate with the MPU6050 sensor. To compile and run the example, follow these steps:

```bash
cd PATH/Software/examples/I2C/MPU6050
```

Compile the example:

```bash
make bin 
```

Flash the binary to your development board:
```bash
make flash
```



## Linux Configuration for USB CDC Devices

To configure permissions for USB CDC devices (/dev/ttyACM0), follow these steps:

Create a new udev rule file:

```bash
sudo nano /etc/udev/rules.d/99-custom-usb.rules
```

Add the following rule to the file (replace idVendor and idProduct with your device's actual IDs):

```bash
SUBSYSTEM=="tty", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="27dd", GROUP="dialout", MODE="0666"
```

Save the file (Ctrl + O in nano, then Enter) and exit nano (Ctrl + X).

Reload udev rules for changes to take effect:

```bash
sudo udevadm control --reload-rules
```
### Example Commands for Serial Communication

Send data to USB device:

```bash
echo -e 'Hello World!\n' > /dev/ttyACM0
```

Read data from USB device:

```bash
picocom /dev/ttyACM0 -b 9600
 ```
These commands allow you to interact with USB CDC devices connected to your Linux system. Adjust the device path (/dev/ttyACM0) as per your setup.

