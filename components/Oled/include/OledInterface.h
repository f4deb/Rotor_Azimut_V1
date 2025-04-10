#ifndef OLED_INTERFACE_INTERFACE_H
#define OLED_INTERFACE_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define OLED_INTERFACE_DEBUG 1

#define OLED_INTERFACE_HEADER "ol"
#define OLED_INTERFACE_HEADER_SIZE 2


#define OLED_INTERFACE_COMMAND_SIZE 1
#define SET_TEXT_OLED_HEADER "T"
#define SET_SCROLL_OLED_HEADER "S"



void oledInterface(char rxBuffer[50]);

#endif