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
#include "../I2c/include/I2c.h"

#include "../../managed_components/espressif__esp_io_expander/include/esp_io_expander.h"
#include "../../managed_components/espressif__esp_io_expander_ht8574/include/esp_io_expander_ht8574.h"

#define TAG "IOButtonBoard"

static int value = 0x77;
static int pin = 0x00;

static esp_io_expander_handle_t io_expander = NULL;

#define TEST_OUTPUT_PINS    (IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1)
#define TEST_INPUT_PINS     (IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3)


void i2c_dev_pcf8574_init(void)
{
    esp_err_t ret = esp_io_expander_new_i2c_ht8574(getI2cBus(), ESP_IO_EXPANDER_I2C_PCF8574_ADDRESS_000, &io_expander);
    if (ESP_OK !=  ret){
        ESP_LOGE(TAG, "HT8574 create returned error");
    }
    else if (ESP_OK ==  ret){
        ESP_LOGI(TAG, "HT8574 create returned succed");
    }
}

void i2c_dev_pcf8574_deinit(void)
{
    esp_err_t ret = esp_io_expander_del(io_expander);
    if (ESP_OK !=  ret){
        ESP_LOGE(TAG, "PCF8574 delete returned error");
    }
    else if (ESP_OK ==  ret){
        ESP_LOGI(TAG, "PCF8574 delete returned succed");
    }
}

void writeOutPutPin(int pin, int value){   
    esp_err_t ret;
    /* Define output pin function */
    ret = esp_io_expander_set_dir(io_expander, pin, IO_EXPANDER_OUTPUT);

    // Print state
    //ret = esp_io_expander_print_state(io_expander);

    ret = esp_io_expander_set_level(io_expander, pin, value);
    
}

void write8OutPutPin(int value){   
    esp_err_t ret;
    /* Define output pin function */
    ret = esp_io_expander_set_dir(io_expander, 0xFF, IO_EXPANDER_OUTPUT);

    // Print state
    ret = esp_io_expander_print_state(io_expander);

    ret = esp_io_expander_set_level(io_expander, value, 1);
    ret = esp_io_expander_set_level(io_expander, value ^ 0xFF, 0);    
}

esp_err_t readInputPin(int pin){

    esp_err_t ret;

    ESP_LOGE(TAG, "PIN Slect: 0x%x", pin);


    /* Test output level function */
    uint32_t input_level_mask = 0;
    ret = esp_io_expander_set_dir(io_expander, pin, IO_EXPANDER_INPUT);
    // Print state
    //ret = esp_io_expander_print_state(io_expander);
    // Get input level
    ret = esp_io_expander_get_level(io_expander, pin, &input_level_mask);
    ESP_LOGI(TAG, "Input level mask: 0x%02" PRIX32, input_level_mask);

    return input_level_mask;

}

void ioButtonBoard_task(void *arg){
    for(;;) {

        value = readInputPin(0xFF);
        //writeOutPutPin(0xFF, 0);

//        writeOutPutPin(value, 0);
        vTaskDelay(pdMS_TO_TICKS(60000));
    }
}
