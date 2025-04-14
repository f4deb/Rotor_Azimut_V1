#include <stdio.h>
#include <string.h>
#include "OledInterface.h"
#include "Oled.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "oled Interface"

void oledInterface(char rxBuffer[50]){

    char str[OLED_INTERFACE_COMMAND_SIZE];
    char value[50];
    if (OLED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, OLED_INTERFACE_COMMAND_SIZE);

    if (OLED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    
    rxBuffer++;        
    
    if ((strcmp(SET_TEXT_OLED_HEADER,str)) == 0) {
        stringToString(str,rxBuffer, strlen(rxBuffer));
        setTextOled(str);
    }  
    
    else if ((strcmp(SET_ROTATION_OLED_HEADER,str)) == 0) {
        setTextRotation(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_LONG_MODE_OLED_HEADER,str)) == 0) {
        setLongMode(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_RECOLOR_OLED_HEADER,str)) == 0) {
        setRecolor(readHex(stringToString(str,rxBuffer,2)));
    }
    
    else {
        ESP_LOGE(TAG, "Bad command");
    }
} 