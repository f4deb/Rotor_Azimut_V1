#include <stdio.h>
#include <string.h>
#include "OledInterface.h"
#include "Oled.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../blueLed/include/blueLed.h"
#include "../interface/include/interface.h"
#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "oled Interface"

void oledInterface(char rxBuffer[50]){

    char str[OLED_INTERFACE_COMMAND_SIZE];
    char value[50];
    if (OLED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, OLED_INTERFACE_COMMAND_SIZE);

    if (OLED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    
    rxBuffer = rxBuffer + OLED_INTERFACE_COMMAND_SIZE;  
    
    if ((strcmp(SET_TEXT_OLED_HEADER,str)) == 0) {
        setTextOled(1, rxBuffer);
    }  

    else if ((strcmp(CREATE_LABEL_OLED_HEADER,str)) == 0) {
        createLabel(1);
    }
    
    else if ((strcmp(SET_ROTATION_OLED_HEADER,str)) == 0) {
        setTextRotation(readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_LONG_MODE_OLED_HEADER,str)) == 0) {
        setLongMode(1,readHex(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_RECOLOR_OLED_HEADER,str)) == 0) {
        setRecolor(1, readHex(stringToString(str,rxBuffer,2)));
    }
    
    else if ((strcmp(SET_X_POS_OLED_HEADER,str)) == 0) {
        setXPos(1, readDec(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_Y_POS_OLED_HEADER,str)) == 0) {
        setYPos(1, readDec(stringToString(str,rxBuffer,2)));
    }

    else if ((strcmp(SET_POS_OLED_HEADER,str)) == 0) {
        int x = readDec(stringToString(str,rxBuffer,2));
        int y = readDec(stringToString(str,rxBuffer+2,2));
        setPos(1, x, y);
    }

    else if ((strcmp(DRAW_RECTANGLE_OLED_HEADER,str)) == 0) {
        int x = readDec(stringToString(str,rxBuffer,2));
        int y = readDec(stringToString(str,rxBuffer+2,2));
        int dimx = readDec(stringToString(str,rxBuffer+4,2));
        int dimy = readDec(stringToString(str,rxBuffer+6,2));
        int size = readDec(stringToString(str,rxBuffer+8,2));

        drawRectangle(x, y, dimx, dimy, size);
    }

    else if ((strcmp(DRAW_LINE_OLED_HEADER,str)) == 0) {
        int x1 = readDec(stringToString(str,rxBuffer,2));
        int y1 = readDec(stringToString(str,rxBuffer+2,2));
        int x2 = readDec(stringToString(str,rxBuffer+4,2));
        int y2 = readDec(stringToString(str,rxBuffer+6,2));
        int size = readDec(stringToString(str,rxBuffer+8,2));

        drawLine(0,x1, y1, x2, y2, size);
    }

    else if ((strcmp(CLEAR_SCREEN_OLED_HEADER,str)) == 0) {
        clearScreen();
    }    
    
    else if ((strcmp(BOUSSOLE_OLED_HEADER,str)) == 0) {
        boussole(readDec(stringToString(str,rxBuffer,3)));    
    }

    else {
        ESP_LOGE(TAG, "Bad command");
    }
} 