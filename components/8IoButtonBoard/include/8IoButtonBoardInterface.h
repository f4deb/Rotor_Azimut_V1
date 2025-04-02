#ifndef IO_BUTTON_BOARD_INTERFACE_H
#define IO_BUTTON_BOARD_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define IO_BUTTON_BOARD_INTERFACE_DEBUG 1

#define IO_BUTTON_BOARD_INTERFACE_HEADER "io"
#define IO_BUTTON_BOARD_INTERFACE_HEADER_SIZE 2

#define IO_BUTTON_BOARD_INTERFACE_COMMAND_SIZE 1
#define IO_OUTPUT_HEADER "w"
#define IO_8_OUTPUT_HEADER "W"
#define IO_INPUT_HEADER "r"
#define IO_8_INPUT_HEADER "R"

void ioButtonBoardInterface(char rxBuffer[50]);

#endif