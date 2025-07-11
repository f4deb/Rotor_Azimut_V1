/*! \copyright 2024 Zorxx Software. All rights reserved.
 *  \license This file is released under the MIT License. See the LICENSE file for details.
 *  \brief rtci2c Library internal interface
 */
#ifndef _SENSORI2C_PRIVATE_H
#define _SENSORI2C_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>
#include "sensori2c/sensori2c.h"
#include "sys.h" /* include after sensori2c.h */

typedef bool (*pfn_sensordevice_init)(void *sensori2c_ctx);
typedef bool (*pfn_sensordevice_datetime)(void *sensori2c_ctx, struct tm *datetime);

typedef struct sensori2c_s
{
    uint8_t i2c_address;
    uint8_t i2c_max_transfer_length;
    uint8_t i2c_timeout;
    uint32_t i2c_speed;

    pfn_sensordevice_init devfn_init;
    pfn_sensordevice_init devfn_deinit;
    pfn_sensordevice_datetime devfn_get_datetime;
    pfn_sensordevice_datetime devfn_set_datetime;

    void *lowlevel;
} sensori2c_t;

#endif /* _SENSORI2C_PRIVATE_H */
