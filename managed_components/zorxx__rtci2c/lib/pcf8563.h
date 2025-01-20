/*! \copyright 2024 Zorxx Software. All rights reserved.
 *  \license This file is released under the MIT License. See the LICENSE file for details.
 *  \brief pcf8563 real-time clock device interface 
 */
#ifndef _PCF8563_H
#define _PCF8563_H

#include <stdint.h>
#include <stdbool.h>
#include "rtci2c_private.h"
#include "helpers.h"

#define PCF8563_I2C_ADDRESS             0x51
#define PCF8563_I2C_SPEED               100000 /* hz */
#define PCF8563_I2C_MAX_TRANSFER_LENGTH 64 /* bytes */
#define PCF8563_I2C_TIMEOUT             20 /* milliseconds */

/* -----------------------------------------------------------------------------------------------
 * Register definitions 
 */

#define PCF8563_REG_SECONDS          2
   #define PCF8563_REG_MASK_SECONDS    0x7f
   #define PCF8563_REG_SECONDS_CS_BIT   7

#define PCF8563_REG_MINUTES          3
   #define PCF8563_REG_MASK_MINUTES    0x7f

#define PCF8563_REG_HOURS            4
#define PCF8563_REG_HOURS_12         4
#define PCF8563_REG_HOURS_24         4
   #define PCF8563_REG_MASK_HOURS_24   0x3f
   #define PCF8563_REG_MASK_HOURS_12   0x1f
   #define PCF8563_REG_HOURS_AMPM_BIT   5 /* 1 = PM, 0 = AM */
   #define PCF8563_REG_HOURS_24_BIT     6 /* 1 = 12 hour, 0 = 24 hour*/

#define PCF8563_REG_DAYOFMONTH       5
   #define PCF8563_REG_MASK_DAYOFMONTH 0x3f

#define PCF8563_REG_DAYOFWEEK        6
   #define PCF8563_REG_MASK_DAYOFWEEK  0x3f

#define PCF8563_REG_MONTH            7
   #define PCF8563_REG_MASK_MONTH      0x1f

#define PCF8563_REG_YEAR             8
   #define PCF8563_REG_MASK_YEAR       0xff

#define PCF8563_REG_CONTROL          7
   #define PCF8563_REG_CONTROL_RS0_BIT  0 /* 0 = 1 Hz       1 = 4.096 kHz */
   #define PCF8563_REG_CONTROL_RS1_BIT  1 /* 2 = 8.192 kHz  3 = 32.768 kHz */
   #define PCF8563_REG_CONTROL_SQWE_BIT 4 /* square wave enable */
   #define PCF8563_REG_CONTROL_OUT_BIT  7 /* output enable */

#define PCF8563_REG_RAM_START        8
#define PCF8563_REG_RAM_END          63  /* total of 56 registers */
#define PCF8563_REG_RAM_COUNT        (PCF8563_REG_RAM_END - PCF8563_REG_RAM_START + 1)

/* -----------------------------------------------------------------------------------------------
 * Helper Macros
 */

#define PCF8563_REG_GET(data, field) \
   RTC_BCD_TO_DEC(data[PCF8563_REG_##field] & PCF8563_REG_MASK_##field)
#define PCF8563_REG_GET_BIT(data, reg, bit) \
   ((data[PCF8563_REG_##reg] & (1 << PCF8563_REG_##bit)) != 0)

bool pcf8563_configure(rtci2c_t *ctx, uint8_t i2c_address);
bool pcf8563_get_datetime(void *rtci2c_ctx, struct tm *datetime);
bool pcf8563_set_datetime(void *rtci2c_ctx, struct tm *datetime);

#endif /* _PCF8563_H */