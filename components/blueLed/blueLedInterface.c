#include <stdio.h>
#include <string.h>
#include "blueLedInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"

#include "../uartCommand/include/uartCommand.h"

#define TAG "Blue Led Interface"

void blueLedInterface(char rxBuffer[50]){

    //char rxBuffer[BUF_SIZE];
    char str[BLUE_LED_INTERFACE_HEADER_SIZE];

    //if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            ESP_LOGE(TAG, "%s ", rxBuffer);

            rxBuffer = rxBuffer + 3;

            strncpy(str,rxBuffer,BLUE_LED_INTERFACE_HEADER_SIZE);
            str[BLUE_LED_INTERFACE_HEADER_SIZE] = '\0';
            ESP_LOGE(TAG, "%s ", str);
            rxBuffer++; 
            
            if ((strcmp(SET_RATIO_BLINK_HEADER,str)) == 0) {
                setRatioBlink(readHex(stringToString(str,rxBuffer,2)));
            }
            else if ((strcmp(SET_TIME_BLINK_HEADER,str)) == 0) {
                setTimeBlink(readHex(stringToString(str,rxBuffer,4)));
            }
            else {
                ESP_LOGE(TAG, "Bad command");
            }
     //   }   
}