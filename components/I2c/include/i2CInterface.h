#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define I2C_INTERFACE_DEBUG 1

#define I2C_INTERFACE_HEADER "i2"
#define I2C_INTERFACE_HEADER_SIZE 2


#define I2C_INTERFACE_COMMAND_SIZE 1
#define I2C_DETECT_HEADER "d"

void i2cInterface(char rxBuffer[50]);


#endif