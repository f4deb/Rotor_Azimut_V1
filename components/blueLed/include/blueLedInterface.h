#ifndef BLUE_LED_INTERFACE_H
#define BLUE_LED_INTERFACE_H


#define SET_TIME_BLINK_HEADER "t"
#define SET_RATIO_BLINK_HEADER "b"

#define BLINK_BLUE_LED "l"


#define SET_BLUE_LED_HEADER "w"
#define GET_BLUE_LED_HEADER "r"

#define BLUE_LED_INTERFACE_HEADER_SIZE 1

void blueLedInterface(char rxBuffer[50]);

#endif