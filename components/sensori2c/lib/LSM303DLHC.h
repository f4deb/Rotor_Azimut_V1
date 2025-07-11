/*! \brief LSM303DLHC magnetomer accelerometer device interface 
 */
#ifndef _LSM303DLHC_H
#define _LSM303DLHC_H

#include <stdint.h>
#include <stdbool.h>
#include "sensori2c_private.h"
#include "helpers.h"

#define LSM303DLHC_MAGNETO_I2C_ADDRESS             0x1E
#define LSM303DLHC_ACCEL_I2C_ADDRESS             0x19
#define LSM303DLHC_I2C_SPEED               100000 /* hz */
#define LSM303DLHC_I2C_MAX_TRANSFER_LENGTH 64 /* bytes */
#define LSM303DLHC_I2C_TIMEOUT             20 /* milliseconds */

#define OUT_X_L_ACCEL           0x28 //register address for accelerometer/magnetometer data
#define OUT_X_L_MEGNETO         0x03

/* -----------------------------------------------------------------------------------------------
 * Register definitions 
 */

#define LSM303DLHC_REG_CONTROL_STATUS_1          0

#define LSM303DLHC_REG_SECONDS          2
   #define LSM303DLHC_REG_MASK_SECONDS    0x7f
   #define LSM303DLHC_REG_SECONDS_CS_BIT   7

#define LSM303DLHC_REG_MINUTES          3
   #define LSM303DLHC_REG_MASK_MINUTES    0x7f

#define LSM303DLHC_REG_HOURS            4
   #define LSM303DLHC_REG_MASK_HOURS  0x3f

#define LSM303DLHC_REG_DAYOFMONTH       5
   #define LSM303DLHC_REG_MASK_DAYOFMONTH 0x3f

#define LSM303DLHC_REG_DAYOFWEEK        6
   #define LSM303DLHC_REG_MASK_DAYOFWEEK  0x07

#define LSM303DLHC_REG_MONTH            7
   #define LSM303DLHC_REG_MASK_MONTH      0x1f

#define LSM303DLHC_REG_YEAR             8
   #define LSM303DLHC_REG_MASK_YEAR       0xff

#define LSM303DLHC_REG_CONTROL          0
   #define LSM303DLHC_REG_CONTROL_RS0_BIT  0 /* 0 = 1 Hz       1 = 4.096 kHz */
   #define LSM303DLHC_REG_CONTROL_RS1_BIT  1 /* 2 = 8.192 kHz  3 = 32.768 kHz */
   #define LSM303DLHC_REG_CONTROL_SQWE_BIT 4 /* square wave enable */
   #define LSM303DLHC_REG_CONTROL_OUT_BIT  7 /* output enable */

#define LSM303DLHC_REG_RAM_START        8
#define LSM303DLHC_REG_RAM_END          63  /* total of 56 registers */
#define LSM303DLHC_REG_RAM_COUNT        (LSM303DLHC_REG_RAM_END - LSM303DLHC_REG_RAM_START + 1)

/* -----------------------------------------------------------------------------------------------
 * Helper Macros
 */

#define LSM303DLHC_REG_GET(data, field) \
   RTC_BCD_TO_DEC(data[LSM303DLHC_REG_##field] & LSM303DLHC_REG_MASK_##field)
#define LSM303DLHC_REG_GET_BIT(data, reg, bit) \
   ((data[LSM303DLHC_REG_##reg] & (1 << LSM303DLHC_REG_##bit)) != 0)

bool pcf8563_configure(sensori2c_t *ctx, uint8_t i2c_address);
bool pcf8563_get_datetime(void *sensori2c_ctx, struct tm *datetime);
bool pcf8563_set_datetime(void *sensori2c_ctx, struct tm *datetime);

#endif /* _LSM303DLHC_H */