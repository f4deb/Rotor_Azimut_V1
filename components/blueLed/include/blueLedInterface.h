#ifndef BLUE_LED_INTERFACE_H
#define BLUE_LED_INTERFACE_H

#include "../../interface/include/interface.h"
#include "../../interface/include/constants.h"

// List of BLUELED COMMAND HEADER

/**
 * Defines the header to set the blue led status
 */
#define COMMAND_SET_BLUE_LED         'w'

/**
 * Defines the header to get the blue led status
 */
#define COMMAND_GET_BLUE_LED         'r'

/**
 * Defines the header to to blink the blue red
 */
#define COMMAND_WRITE_DATE         'b'


#endif