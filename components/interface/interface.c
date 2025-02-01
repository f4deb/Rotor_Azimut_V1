#include <stdio.h>
#include "interface.h"
#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "esp_log.h"

#include "constants.h"

#include "../interface/include/constants.h"
#include "../interface/include/interface.h"

#include "../charUtils/include/charUtils.h"

static const char *TAG_INTERFACE = "INTERFACE";

void interface_task(void *arg){
    for(;;) {
        ESP_LOGI(TAG_INTERFACE, "Interface Debug");

        char *text = "bl";

        if (strncmp(text, BLUE_LED_HEADER, 2) == 0) {
            printf("Les cinq premiers caractères sont égaux.\n");
        } else {
            printf("Les cinq premiers caractères ne sont pas égaux.\n");
        }

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
