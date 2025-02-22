#include <stdio.h>
#include <string.h>
#include "interface.h"

#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "../uartCommand/include/uartCommand.h"
#include "../blueLed/include/blueLed.h"
#include "../blueLedInterface/include/blueLedInterface.h"

#define TAG "UART2"

bool isCommandRx;

void initInterface (void){

}

void interface_task(void *arg){
        char rxBuffer[BUF_SIZE];
        char str[INTERFACE_HEADER_SIZE];

    for(;;) {
        if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            ESP_LOGI(TAG, "%s ", rxBuffer);

            strncpy(str,rxBuffer,INTERFACE_HEADER_SIZE);
            str[INTERFACE_HEADER_SIZE] = '\0';
            //ESP_LOGE(TAG, "%s ", str);
            //ESP_LOGE(TAG, "%s ", rxBuffer);


            if ((strcmp(INTERFACE_HEADER,str)) == 0) {
                blueLedInterface(rxBuffer);
            }
            else {
                setRatioBlink(50);
            }
        }   
    vTaskDelay(pdMS_TO_TICKS(500));
    }
}