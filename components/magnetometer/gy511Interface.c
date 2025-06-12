#include <stdio.h>
#include <string.h>
#include "gy511Interface.h"
#include "gy511.h"


#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "GY-511 Interface"

void gy511Interface(char rxBuffer[50]){

    char str[GY511_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (GY511_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, GY511_INTERFACE_COMMAND_SIZE);

    if (GY511_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
 
    rxBuffer++;        
    
    if ((strcmp(GET_MAG_X_HEADER,str)) == 0) {
        gy511();
        if (GY511_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    
    else {
        ESP_LOGE(TAG, "Bad GY command");
    }
}