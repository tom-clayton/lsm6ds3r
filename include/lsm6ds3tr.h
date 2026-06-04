/*
 * lsm6ds3tr.h: Minimal LSM6DS3TR sensor driver for gesture recognition. 
 *
 * Sets up the sensor to detect a particular guesture and generate an interrupt.
 *
 * Requires I2C bus read / write functions to be passed in, as declared in i2c_wrapper.h.
 * 
 * Tom Clayton 2025
 * 
 */

#ifndef ILSM6DS3TR_H
#define ILSM6DS3TR_H

#include <stdint.h>
#include "i2c_wrapper.h"

#define LSM6DS_ID_REG	0x0F
#define LSM6DS_CTRL1_XL_REG 0x10
#define LSM6DS_CTRL6_C_REG 0x15
#define LSM6DS_DRDY_PULSE_CFG_REG 0x1B
#define LSM6DS_TAP_SRC_REG 0x1B
#define LSM6DS_STATUS_REG 0x1E
#define LSM6DS_CTRL8_XL_REG 0x22
#define LSM6DS_CTRL4_C_REG 0x23
#define LSM6DS_TAP_CFG_REG 0x58
#define LSM6DS_TAP_THS_6D_REG 0x59
#define LSM6DS_INT_DUR2_REG 0x5A
#define LSM6DS_WAKE_UP_THS_REG 0x5B
#define LSM6DS_MD1_CFG_REG 0x5E
#define LSM6DS_CTRL10_C_REG 0x60

#define LSM6DS_CHIP_ID	0x6A

/*
 * Initialise the LSM6DS sensor
 * 
 * @param i2c_bus: The I2C bus that the sensor is connected to.
 * 
 * @return 0 on success, -1 on failure
 */
int lsm6ds_init(const i2c_bus_t *i2c_bus);

/*
 * Set the device to detect taps.
 */
void lsm6ds_setup_tap();

/*
 * Set the device to detect absolute wrist tilts.
 */
void lsm6ds_setup_AWT();

/*
 * Set the device to detect 6D orientation changes.
 */
void lsm6ds_setup_6D();

/*
 * Helper function to read arbitrary register.
 */
uint8_t lsm6ds_read_reg(uint8_t reg);

#endif