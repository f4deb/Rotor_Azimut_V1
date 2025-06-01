#include <stdio.h>
#include <string.h>
#include "interface.h"

#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "../uartCommand/include/uartCommand.h"
#include "../blueLed/include/blueLed.h"
#include "../blueLed/include/blueLedInterface.h"
#include "../clock/include/clockInterface.h"
#include "../8IoButtonBoard/include/8IoButtonBoardInterface.h"
#include "../Oled/include/OledInterface.h"
#include "../I2c/include/i2CInterface.h"

#define TAG "UART2"

void interface_task(void *arg){
    char rxBuffer[BUF_SIZE];
    char str[INTERFACE_HEADER_SIZE];

    for(;;) {
        if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            ESP_LOGI(TAG, "%s ", rxBuffer);
            stringToString(str,rxBuffer,INTERFACE_HEADER_SIZE);
            ESP_LOGI(TAG, "%s ", str);
            if ((strcmp(INTERFACE_HEADER,str)) == 0) {

                stringToString(str,rxBuffer+3,2);
                ESP_LOGI(TAG, "%s ", str);


                // blueLed
                if ((strcmp(BLUE_LED_INTERFACE_HEADER,str)) == 0) {
                    blueLedInterface(rxBuffer+5);
                }
                // Clock
                else if ((strcmp(CLOCK_INTERFACE_HEADER,str)) == 0) {
                    clockInterface(rxBuffer+5);
                }
                // 8IoButtonBoard
                else if ((strcmp(IO_BUTTON_BOARD_INTERFACE_HEADER,str)) == 0) {
                    ioButtonBoardInterface(rxBuffer+5);
                }     
                // I2C
                else if ((strcmp(I2C_INTERFACE_HEADER,str)) == 0) {
                    i2cInterface(rxBuffer+5);
                }                    
                // Oled
                else if ((strcmp(OLED_INTERFACE_HEADER,str)) == 0) {
                    oledInterface(rxBuffer+5);
}


                    
            }
            else {
                setRatioBlink(50);
            }
            
        }   
    vTaskDelay(pdMS_TO_TICKS(500));
    }
}