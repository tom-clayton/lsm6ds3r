/*
 * lsm6ds3tr.c: Minimal LSM6DS3TR sensor driver for gesture recognition. 
 *
 * Sets up the sensor to detect a particular guesture and generate an interrupt.
 *
 * Tom Clayton 2025
 * 
 */

#include "lsm6ds3tr.h"

static const i2c_bus_t *bus;

int lsm6ds_init(const i2c_bus_t *i2c_bus)
{
    bus = i2c_bus;

    uint8_t id;
    if (bus->i2c_read_reg(LSM6DS_ID_REG, &id) == 0){
        return (id == LSM6DS_CHIP_ID) ? 0 : -1;
    } else { 
        return -1; 
    }
}

void lsm6ds_setup_tap()
{   bus->i2c_write_reg(LSM6DS_CTRL1_XL_REG, 0x60);       // Turn on accelerometer 
    bus->i2c_write_reg(LSM6DS_CTRL6_C_REG, 0x00);        // High-performance operating mode enabled for accelerometer
    bus->i2c_write_reg(LSM6DS_TAP_CFG_REG, 0x8E);        // Enable interrupts and enable tap detection on all axis
    bus->i2c_write_reg(LSM6DS_TAP_THS_6D_REG, 0x8C);     // Set tap threshold
    bus->i2c_write_reg(LSM6DS_INT_DUR2_REG, 0x7F);       // Set duration, quiet and shock time windows
    bus->i2c_write_reg(LSM6DS_WAKE_UP_THS_REG, 0x80);    // Enable double tap 
    bus->i2c_write_reg(LSM6DS_MD1_CFG_REG, 0x08);        // Route double tap interrupt to INT1 pin 
}

void lsm6ds_setup_AWT()
{   bus->i2c_write_reg(LSM6DS_CTRL1_XL_REG, 0x20);       // Turn on accelerometer 
    bus->i2c_write_reg(LSM6DS_CTRL6_C_REG, 0x10);        // High-performance operating mode disabled for accelerometer
    bus->i2c_write_reg(LSM6DS_CTRL10_C_REG, 0x84);       // Enable tilt detection
    bus->i2c_write_reg(LSM6DS_DRDY_PULSE_CFG_REG, 0x01); // Set interupt 
    bus->i2c_write_reg(LSM6DS_CTRL4_C_REG, 0x20);        // INT 2 to INT 1 pin
}

void lsm6ds_setup_6D()
{   bus->i2c_write_reg(LSM6DS_CTRL1_XL_REG, 0x20);       // Turn on accelerometer 
    bus->i2c_write_reg(LSM6DS_CTRL6_C_REG, 0x10);        // High-performance operating mode disabled for accelerometer
    bus->i2c_write_reg(LSM6DS_TAP_CFG_REG, 0x80);        // Enable interrupts
    bus->i2c_write_reg(LSM6DS_TAP_THS_6D_REG, 0x20);     // Set 6D threshold
    bus->i2c_write_reg(LSM6DS_CTRL8_XL_REG, 0x40);       // Setup filter
    bus->i2c_write_reg(LSM6DS_MD1_CFG_REG, 0x04);        // Route 6D orientation change interrupt to INT1 pin

}

uint8_t lsm6ds_read_reg(uint8_t reg)
{
    uint8_t data;
    bus->i2c_read_reg(reg, &data); 
    return data; 
}

   