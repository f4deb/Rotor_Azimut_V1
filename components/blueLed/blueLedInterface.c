#include <stdio.h>
#include <string.h>
#include "blueLedInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "Blue Led Interface"

void blueLedInterface(char rxBuffer[50]){

    //char rxBuffer[BUF_SIZE];
    char str[BLUE_LED_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    rxBuffer += INTERFACE_HEADER_SIZE;

    stringToString(str,rxBuffer, BLUE_LED_INTERFACE_HEADER_SIZE);

    //strncpy(str,rxBuffer,BLUE_LED_INTERFACE_HEADER_SIZE);
    //str[BLUE_LED_INTERFACE_HEADER_SIZE] = '\0';
    if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer += BLUE_LED_INTERFACE_HEADER_SIZE;

    if ((strcmp(BLUE_LED_INTERFACE_HEADER,str)) == 0) {         

        strncpy(str,rxBuffer,BLUE_LED_INTERFACE_COMMAND_SIZE);
        str[BLUE_LED_INTERFACE_COMMAND_SIZE] = '\0';
        ESP_LOGE(TAG, "%s ", str);
        rxBuffer++;        
        
        if ((strcmp(SET_RATIO_BLINK_HEADER,str)) == 0) {
            setRatioBlink(readHex(stringToString(str,rxBuffer,2)));
            if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(SET_TIME_BLINK_HEADER,str)) == 0) {
            setTimeBlink(readHex(stringToString(str,rxBuffer,4)));
            if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(SET_BLUE_LED_HEADER,str)) == 0) {
            setBlueLed(readHex(stringToString(str,rxBuffer,2)));
            if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        }
        else if ((strcmp(GET_BLUE_LED_HEADER,str)) == 0) {
            bool s_led_state;
            if (getBlueLed()){
                s_led_state = true;
            }
            else {
                s_led_state = false;
            }
            if (BLUE_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "LED Status : %s", s_led_state == true ? "ON" : "OFF");

            sprintf (status,"%02d", s_led_state );
            
                
        // Write data back to the UART
        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));
        status [0] = LF;
        status [1] = '\0';


        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));

            }
            else {
                ESP_LOGE(TAG, "Bad command");
            }
    }
    else {
                ESP_LOGE(TAG, "Bad command");
            }

}