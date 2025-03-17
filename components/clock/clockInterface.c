#include <stdio.h>
#include <string.h>
#include "clockInterface.h"
#include "clock.h"

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
    char value[20];
    if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, CLOCK_INTERFACE_COMMAND_SIZE);

    if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    
    rxBuffer++;        
    
    if ((strcmp(READ_CLOCK_HEADER,str)) == 0) {
        readClock();
        if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    else if ((strcmp(WRITE_CLOCK_HEADER,str)) == 0) {

        if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    else if ((strcmp(SET_ALARM_HEADER,str)) == 0) {

        if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    else if ((strcmp(GET_ALARM_HEADER,str)) == 0) {

    }
    else if ((strcmp(WRITE_HOUR_HEADER,str)) == 0) {
        setHour(readHex(stringToString(str,rxBuffer,2)));

    }
    else if ((strcmp(WRITE_MINUTE_HEADER,str)) == 0) {
        setMinute(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(WRITE_SECONDE_HEADER,str)) == 0) {
        setSeconde(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(WRITE_DAY_HEADER,str)) == 0) {
        setDay(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(WRITE_MONTH_HEADER,str)) == 0) {
        setMonth(readHex(stringToString(str,rxBuffer,2)));    
    }

    else if ((strcmp(WRITE_YEAR_HEADER,str)) == 0) {
        setYear(readHex(stringToString(str,rxBuffer,2)));       
        
    }

    else if ((strcmp(READ_SECONDE_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getSeconde() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';
    }

    else if ((strcmp(READ_MINUTE_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getMinute() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';        
    }

    else if ((strcmp(READ_HOUR_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getHour() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';
    }

    else if ((strcmp(READ_DAY_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getDay() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';
    }

    else if ((strcmp(READ_MONTH_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getMonth() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';
    }

    else if ((strcmp(READ_YEAR_HEADER,str)) == 0) {             
        sprintf (value,"%02d", getYear() );        
        uart_write_bytes(COMMAND_UART_PORT_NUM, value, strlen(value));
        value [2] = '\0';

    }
    else {
        ESP_LOGE(TAG, "Bad command");
    }
  

}