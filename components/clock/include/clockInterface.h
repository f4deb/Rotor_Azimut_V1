#ifndef CLOCK_INTERFACE_INTERFACE_H
#define CLOCK_INTERFACE_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define CLOCK_INTERFACE_DEBUG 1

#define CLOCK_INTERFACE_HEADER "cl"
#define CLOCK_INTERFACE_HEADER_SIZE 2


#define CLOCK_INTERFACE_COMMAND_SIZE 1
#define READ_CLOCK_HEADER "r"
#define WRITE_CLOCK_HEADER "w"

#define SET_ALARM_HEADER "s"
#define GET_ALARM_HEADER "g"

#define WRITE_HOUR_HEADER "H"

void clockInterface(char rxBuffer[50]);

#endif