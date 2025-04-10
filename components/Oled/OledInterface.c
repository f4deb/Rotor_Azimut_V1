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
            
        //if (OLED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", getTextOled());

        //oled();
    }
   
    
    /*else if ((strcmp(SET_OLED_REFRESH_DELAY,str)) == 0) {
        setOledRefresh(readDec(stringToString(str,rxBuffer,6)));
    }
    */
    else {
        ESP_LOGE(TAG, "Bad command");
    }
} 