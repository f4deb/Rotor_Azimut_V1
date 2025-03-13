#include <stdio.h>
#include <string.h>
#include "clockInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "Clock Interface"

void clockInterface(char rxBuffer[50]){

    char str[CLOCK_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    rxBuffer += INTERFACE_HEADER_SIZE;

    stringToString(str,rxBuffer, CLOCK_INTERFACE_HEADER_SIZE);

    if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer += CLOCK_INTERFACE_HEADER_SIZE;

    if ((strcmp(CLOCK_INTERFACE_HEADER,str)) == 0) {         

        strncpy(str,rxBuffer,CLOCK_INTERFACE_COMMAND_SIZE);
        str[CLOCK_INTERFACE_COMMAND_SIZE] = '\0';
        ESP_LOGE(TAG, "%s ", str);
        rxBuffer++;        
        
        if ((strcmp(READ_CLOCK_HEADER,str)) == 0) {
            //setRatioBlink(readHex(stringToString(str,rxBuffer,2)));
            if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(WRITE_CLOCK_HEADER,str)) == 0) {
            //setTimeBlink(readHex(stringToString(str,rxBuffer,4)));
            if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(SET_ALARM_HEADER,str)) == 0) {
            //setBlueLed(readHex(stringToString(str,rxBuffer,2)));
            if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(GET_ALARM_HEADER,str)) == 0) {
            //setBlueLed(readHex(stringToString(str,rxBuffer,2)));
            if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "LED Status : %s", s_led_state == true ? "ON" : "OFF");

            
            
                
        // Write data back to the UART
        /*uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));
        status [0] = LF;
        status [1] = '\0';


        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));
        */    
            }
            else {
                ESP_LOGE(TAG, "Bad command");
            }
    }
    else {
                ESP_LOGE(TAG, "Bad command");
            }

}