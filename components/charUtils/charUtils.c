#include <stdio.h>
#include "charUtils.h"
#include "string.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#define TAG "CHAR UTILS"


char* truncString(char* str,int posInit, int length){

    size_t len = strlen(str);

    str  = str + posInit;
    str[length] = '\0';
    return str;
}

char* stringToString(char* str,char* rxBuffer,int size){

    strncpy(str,rxBuffer,size);
                str[size] = '\0';
                //ESP_LOGE(TAG, "%s ", str);
    return str;
}



int readHex(char* str) {
    int result;
    if (sscanf(str, "%d", &result) ==1) {
         //ESP_LOGE(TAG, "Converted integer: %d\n", result);
    }
    else {
        ESP_LOGE(TAG, "Conversion failed.\n");
    }

    return result;
}