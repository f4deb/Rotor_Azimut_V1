#include <stdio.h>
#include <string.h>
#include "blueLedInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"
#define TAG "Blue Led Interface"

void blueLedInterface(char rxBuffer[50]){

    //char rxBuffer[BUF_SIZE];
    char str[BLUE_LED_INTERFACE_HEADER_SIZE];
    char status[20];
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
            else if ((strcmp(SET_BLUE_LED_HEADER,str)) == 0) {
                setBlueLed(readHex(stringToString(str,rxBuffer,2)));
            }
            else if ((strcmp(GET_BLUE_LED_HEADER,str)) == 0) {
                bool s_led_state;
                if (getBlueLed()){
                    s_led_state = true;
                }
                else {
                    s_led_state = false;
                }

                //ESP_LOGI(TAG, "LED Status : %s", s_led_state == true ? "ON" : "OFF");

                sprintf (status,"%02d", s_led_state );
                
        // Write data back to the UART
        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));

            }
            else {
                ESP_LOGE(TAG, "Bad command");
            }
     //   }   
}