#ifndef SENSOR_INTERFACE_INTERFACE_H
#define SENSOR_INTERFACE_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define SENSOR_INTERFACE_DEBUG 1

#define SENSOR_INTERFACE_HEADER "gy"
#define SENSOR_INTERFACE_HEADER_SIZE 2


#define SENSOR_INTERFACE_COMMAND_SIZE 1
#define READ_MAG_X_HEADER "x"
#define READ_MAG_Y_HEADER "y"
#define READ_MAG_Z_HEADER "z"

void sensorInterface(char rxBuffer[50]);

#endif