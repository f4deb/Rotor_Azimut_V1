#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "8IoButtonBoard.h"
#include "8IoButtonBoardInterface.h"

#include <stdio.h>
#include <string.h>

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../8IoButtonBoard/include/8IoButtonBoard.h"

#define TAG "IOButtonBoard"

char value = 0x77;

void writeOutPut(int value)
{         ESP_LOGI(TAG,"8 IO Button Board");


}

int readInput(void){
    return 0;
}

void ioButtonBoard_task(void *arg){
    for(;;) {
        value = !value;
        writeOutPut(value);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
