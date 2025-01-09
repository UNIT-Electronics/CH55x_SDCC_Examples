#include "src/system.h"
#include "src/delay.h"
#include "src/usb_cdc.h"
#include "src/i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MPU6050_ADDR 0x68
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_TEMP_OUT_H 0x41

void USB_interrupt(void);

// Prototypes
void MPU6050_init(void);
void MPU6050_read(__xdata int16_t *accel, __xdata int16_t *gyro, __xdata int16_t *temp);
void CDC_print_int16(int16_t value);

// Implementación de itoa
void itoa(int16_t value, char *buffer, uint8_t base);

void USB_ISR(void) __interrupt(INT_NO_USB) {
    USB_interrupt();
}

// Main function
void main(void) {
    __xdata int16_t accel[3], gyro[3], temp;

    CLK_config();
    DLY_ms(5); // Wait for clock to stabilize
    I2C_init();
    MPU6050_init();
    CDC_init();
    for (uint8_t i = 0; i < 10; i++) {
        DLY_ms(100);
        CDC_print(".");
      
    }

    while (1) {
        MPU6050_read(accel, gyro, &temp);

        // Print raw data
        CDC_print("Raw Accel: ");
        CDC_print_int16(accel[0]);
        CDC_print(" ");
        CDC_print_int16(accel[1]);
        CDC_print(" ");
        CDC_print_int16(accel[2]);

        CDC_print(" Raw Gyro: ");
        CDC_print_int16(gyro[0]);
        CDC_print(" ");
        CDC_print_int16(gyro[1]);
        CDC_print(" ");
        CDC_print_int16(gyro[2]);

        CDC_print(" Raw Temp: ");
        CDC_print_int16(temp);
        CDC_println("\r\n");

        DLY_ms(100);
    }
}

void MPU6050_init(void) {
    I2C_start((uint8_t)(MPU6050_ADDR << 1)); // Start I2C and write address
    I2C_write(MPU6050_PWR_MGMT_1);           // Access Power Management 1 register
    I2C_write(0x00);                         // Wake up sensor
    I2C_stop();                              // Stop I2C communication
}

void MPU6050_read(__xdata int16_t *accel, __xdata int16_t *gyro, __xdata int16_t *temp) {
    I2C_start((uint8_t)(MPU6050_ADDR << 1));
    I2C_write(MPU6050_ACCEL_XOUT_H);
    I2C_restart((uint8_t)(MPU6050_ADDR << 1) | 1);

    accel[0] = (I2C_read(1) << 8) | I2C_read(1); // X
    accel[1] = (I2C_read(1) << 8) | I2C_read(1); // Y
    accel[2] = (I2C_read(1) << 8) | I2C_read(1); // Z

    *temp = (I2C_read(1) << 8) | I2C_read(1);

    gyro[0] = (I2C_read(1) << 8) | I2C_read(1); // X
    gyro[1] = (I2C_read(1) << 8) | I2C_read(1); // Y
    gyro[2] = (I2C_read(0) << 8) | I2C_read(0); // Z

    I2C_stop();
}

// Implementación de itoa
void itoa(int16_t value, char *buffer, uint8_t base) {
    char *ptr = buffer;
    char *ptr1 = buffer;
    char tmp_char;
    int tmp_value;

    // Manejar el signo
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    tmp_value = value;

    // Convertir el valor al revés
    do {
        *ptr++ = "0123456789ABCDEF"[tmp_value % base];
        tmp_value /= base;
    } while (tmp_value);

    *ptr-- = '\0';

    // Invertir la cadena
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

void CDC_print_int16(int16_t value) {
    char buffer[8];
    itoa(value, buffer, 10); // Convierte el entero a cadena en base 10
    CDC_print(buffer);
    // flush(); cdc
    CDC_flush();
}
