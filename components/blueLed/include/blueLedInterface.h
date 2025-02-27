#ifndef BLUE_LED_INTERFACE_H
#define BLUE_LED_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define BLUE_LED_INTERFACE_DEBUG 1

#define BLUE_LED_INTERFACE_HEADER "bl"
#define BLUE_LED_INTERFACE_HEADER_SIZE 2


#define BLUE_LED_INTERFACE_COMMAND_SIZE 1
#define SET_TIME_BLINK_HEADER "t"
#define SET_RATIO_BLINK_HEADER "b"

#define BLINK_BLUE_LED "l"


#define SET_BLUE_LED_HEADER "w"
#define GET_BLUE_LED_HEADER "r"

void blueLedInterface(char rxBuffer[50]);

#endif