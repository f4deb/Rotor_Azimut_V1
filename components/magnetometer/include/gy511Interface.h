#ifndef GY511_INTERFACE_H
#define GY511_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define GY511_INTERFACE_DEBUG 1

#define GY511_INTERFACE_HEADER "GY"
#define GY511_INTERFACE_HEADER_SIZE 2


#define GY511_INTERFACE_COMMAND_SIZE 1
#define GET_MAG_X_HEADER "x"

void gy511Interface(char rxBuffer[50]);

#endif