#ifndef OLED_INTERFACE_INTERFACE_H
#define OLED_INTERFACE_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define OLED_INTERFACE_DEBUG 1

#define OLED_INTERFACE_HEADER "cl"
#define OLED_INTERFACE_HEADER_SIZE 2


#define OLED_INTERFACE_COMMAND_SIZE 1
#define READ_OLED_HEADER "r"
#define WRITE_OLED_HEADER "w"



void oledInterface(char rxBuffer[50]);

#endif