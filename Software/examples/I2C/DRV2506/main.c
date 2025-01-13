#include "src/system.h"
#include "src/delay.h"
#include "src/usb_cdc.h"
#include "src/i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRV2605L_ADDR 0x5A
#define DRV2605L_MODE 0x01
#define DRV2605L_GO 0x0C
#define DRV2605L_WAVESEQ1 0x04
#define DRV2605L_OVERDRIVE_CLAMP 0x17
#define DRV2605L_RATED_VOLTAGE 0x16
#define DRV2605L_LIBRARY 0x03
#define DRV2605L_FEEDBACK 0x1A
#define DRV2605L_CONTROL1 0x1B
#define DRV2605L_CONTROL2 0x1C
#define DRV2605L_CONTROL3 0x1D

// Prototypes
void DRV2605L_init(void);
void DRV2605L_setVoltage(uint8_t rated, uint8_t overdrive);
void DRV2605L_selectLibrary(uint8_t library);
void DRV2605L_setWaveform(uint8_t slot, uint8_t effect);
void DRV2605L_go(void);
void DRV2605L_stop(void);
void DRV2605L_configureFeedback(uint8_t use_erm);
void DRV2605L_configureControl(void);

// Main function
void main(void) {
    CLK_config();
    DLY_ms(5);
    I2C_init();
    DRV2605L_init();

    DRV2605L_setVoltage(0x80, 0x90);  // 3.3V operation
    DRV2605L_selectLibrary(1);        // ERM library

    // Ramp effect example
    DRV2605L_setWaveform(0, 47);
    DRV2605L_setWaveform(1, 48);
    DRV2605L_setWaveform(2, 0);
    DRV2605L_go();
    DLY_ms(1000);
    DRV2605L_stop();
}

// Function definitions
void DRV2605L_init(void) {
    DRV2605L_configureFeedback(1);  // Configure for ERM
    DRV2605L_configureControl();   // Configure control registers
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_MODE);
    I2C_write(0x00);  // Internal trigger mode
    I2C_stop();
}

void DRV2605L_setVoltage(uint8_t rated, uint8_t overdrive) {
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_RATED_VOLTAGE);
    I2C_write(rated);
    I2C_stop();

    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_OVERDRIVE_CLAMP);
    I2C_write(overdrive);
    I2C_stop();
}

void DRV2605L_selectLibrary(uint8_t library) {
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_LIBRARY);
    I2C_write(library);
    I2C_stop();
}

void DRV2605L_setWaveform(uint8_t slot, uint8_t effect) {
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_WAVESEQ1 + slot);
    I2C_write(effect);
    I2C_stop();
}

void DRV2605L_go(void) {
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_GO);
    I2C_write(0x01);
    I2C_stop();
}

void DRV2605L_stop(void) {
    DRV2605L_setWaveform(0, 0);
    DRV2605L_go();
}

void DRV2605L_configureFeedback(uint8_t use_erm) {
    uint8_t feedback;
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_FEEDBACK);
    I2C_restart((DRV2605L_ADDR << 1) | 1);
    feedback = I2C_read(0);
    I2C_stop();

    if (use_erm) {
        feedback &= ~0x80;
    } else {
        feedback |= 0x80;
    }

    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_FEEDBACK);
    I2C_write(feedback);
    I2C_stop();
}

void DRV2605L_configureControl(void) {
    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_CONTROL1);
    I2C_write(0x93);
    I2C_stop();

    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_CONTROL2);
    I2C_write(0xF5);
    I2C_stop();

    I2C_start(DRV2605L_ADDR << 1);
    I2C_write(DRV2605L_CONTROL3);
    I2C_write(0xA0);
    I2C_stop();
}
