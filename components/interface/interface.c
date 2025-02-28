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

#define TAG "UART2"

void interface_task(void *arg){
    char rxBuffer[BUF_SIZE];
    char str[INTERFACE_HEADER_SIZE];

    for(;;) {
        if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            ESP_LOGI(TAG, "%s ", rxBuffer);
            stringToString(str,rxBuffer,INTERFACE_HEADER_SIZE);
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