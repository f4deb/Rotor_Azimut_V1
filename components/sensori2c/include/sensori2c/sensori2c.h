
#ifndef _SENSORI2C_H
#define _SENSORI2C_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "sys_esp.h"

typedef void *sensori2c_context;

typedef enum
{
   SENSORI2C_DEVICE_GY511,
   SENSORI2C_DEVICE_GYXXX

} sensori2c_device_type;

sensori2c_context sensori2c_init(sensori2c_device_type device, uint8_t i2c_address, i2c_lowlevel_config *config);
bool sensori2c_deinit(sensori2c_context context);
bool sensori2c_get_datetime(sensori2c_context context, struct tm *datetime);
bool sensori2c_set_datetime(sensori2c_context context, struct tm *datetime);

#endif /* _SENSORI2C_H */
