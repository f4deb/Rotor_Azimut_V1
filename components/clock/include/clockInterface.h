#ifndef CLOCK_INTERFACE_INTERFACE_H
#define CLOCK_INTERFACE_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define CLOCK_INTERFACE_DEBUG 1

#define CLOCK_INTERFACE_HEADER "cl"
#define CLOCK_INTERFACE_HEADER_SIZE 2


#define CLOCK_INTERFACE_COMMAND_SIZE 1
#define READ_CLOCK_HEADER "r"
#define WRITE_CLOCK_HEADER "w"

#define SET_ALARM_HEADER "A"
#define GET_ALARM_HEADER "a"

#define READ_SECONDE_HEADER "s"
#define READ_MINUTE_HEADER "m"
#define READ_HOUR_HEADER "h"
#define READ_DAY_HEADER "d"
#define READ_MONTH_HEADER "t"
#define READ_YEAR_HEADER "y"

#define WRITE_SECONDE_HEADER "S"
#define WRITE_MINUTE_HEADER "M"
#define WRITE_HOUR_HEADER "H"
#define WRITE_DAY_HEADER "D"
#define WRITE_MONTH_HEADER "T"
#define WRITE_YEAR_HEADER "Y"

#define SET_CLOCK_REFRESH_DELAY "C"
#define GET_CLOCK_REFRESH_DELAY "c"

void clockInterface(char rxBuffer[50]);

#endif