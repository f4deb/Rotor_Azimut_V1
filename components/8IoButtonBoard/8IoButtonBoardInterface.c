#include <stdio.h>
#include <string.h>
#include "8IoButtonBoardInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../8IoButtonBoard/include/8IoButtonBoard.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "8IoButtonBoard Interface"

char value[20];
 int result = 0x77;



void ioButtonBoardInterface(char rxBuffer[50]){
    char str[IO_BUTTON_BOARD_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, IO_BUTTON_BOARD_INTERFACE_COMMAND_SIZE);

    if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", str);
 
    rxBuffer++;        
    
    if ((strcmp(IO_OUTPUT_HEADER,str)) == 0) {
        int pin = readHex(stringToString(str,rxBuffer,2));
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "Pin%X ", pin);
        int value = readHex(stringToString(str,rxBuffer+2,2));
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "Value%X ", value);
        writeOutPutPin(pin, value);
    }

    else if ((strcmp(IO_8_OUTPUT_HEADER,str)) == 0) {
        int value = readHex(stringToString(str,rxBuffer,2));
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "Value%X ", value);
        write8OutPutPin(value);
    }

    else if ((strcmp(IO_INPUT_HEADER,str)) == 0) {
        int pin = readHex(stringToString(str,rxBuffer,2));    
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "Pin%X ", pin);

        int result = readInputPin(pin);
        if (result > 0) result = 1;
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "result%X ", result);

        sprintf (value,"%02x", result);       
        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
    }

    else if ((strcmp(IO_8_INPUT_HEADER,str)) == 0) {
        int result = readInputPin(0xFF);
        
        if (IO_BUTTON_BOARD_INTERFACE_DEBUG) ESP_LOGI(TAG, "result%X ", result);

        sprintf (value,"%02x", result);       
        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
    }

    else {
        ESP_LOGE(TAG, "Bad command");
    }
}