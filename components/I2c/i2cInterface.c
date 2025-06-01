#include <stdio.h>
#include <string.h>
#include "i2CInterface.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../I2c/include/I2c.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"

#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "I2C Interface"

void i2cInterface(char rxBuffer[50]){

    char str[I2C_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (I2C_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, I2C_INTERFACE_COMMAND_SIZE);

    if (I2C_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
 
    rxBuffer++;        
    
    if ((strcmp(I2C_DETECT_HEADER,str)) == 0) {
        do_i2cdetect_cmd();
        if (I2C_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    else {
        ESP_LOGE(TAG, "Bad command");
    }
}