#include <stdio.h>
#include "interface.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "esp_log.h"

#include "constants.h"

static const char *TAG_INTERFACE = "INTERFACE";

void interface_task(void *arg){
    for(;;) {
        ESP_LOGI(TAG_INTERFACE, "Interface Debug");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
