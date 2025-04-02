#ifndef I2C_H
#define I2C_H

#include "driver/i2c_master.h"

/* The following definitions may change, based on the ESP device,
RTC device configuration, and wiring between them. */
#define ESP_I2C_PORT I2C_NUM_0
#define ESP_I2C_SDA  GPIO_NUM_21
#define ESP_I2C_SCL  GPIO_NUM_22
#define DEVICE_I2C_ADDRESS 0 /* let the library figure it out */

/* I2C ADDRESS DEFINITION*/
#define ESP_IO_EXPANDER_I2C_PCF8574_ADDRESS_000 0x20


i2c_master_bus_handle_t getI2cBus (void);

void I2cBusInit(void);

#endif