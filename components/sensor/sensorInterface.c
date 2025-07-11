#include <stdio.h>
#include <string.h>
#include "sensorInterface.h"
#include "sensor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "Sensor Interface"

void sensorInterface(char rxBuffer[50]){

    char str[SENSOR_INTERFACE_COMMAND_SIZE];
    char value[20];
    if (SENSOR_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, SENSOR_INTERFACE_COMMAND_SIZE);

    if (SENSOR_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    
    rxBuffer++;        
    
    if ((strcmp(READ_MAG_X_HEADER,str)) == 0) {        
        if (SENSOR_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
        
    }
  
    else {
        ESP_LOGE(TAG, "Bad command");
    }
} 