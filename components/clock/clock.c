#include <stdio.h>
#include "clock.h"
#include "clockInterface.h"

#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "driver/i2c_master.h"
#include "rtci2c/rtci2c.h"

#include "../uartCommand/include/uartCommand.h"

#define TAG "RTCI2C"

#define RTCI2C_LIBRARY_I2C_BUS_INIT 0

/* The following definitions may change, based on the ESP device,
   RTC device configuration, and wiring between them. */
#define ESP_I2C_PORT I2C_NUM_0
#define ESP_I2C_SDA  GPIO_NUM_21
#define ESP_I2C_SCL  GPIO_NUM_22
#define DEVICE_I2C_ADDRESS 0 /* let the library figure it out */

static i2c_master_bus_handle_t i2c_bus;
static i2c_lowlevel_config config = {0}; /* ensure initialize to zero */

void setSeconde(int value){    
    setTime(0,value);
}

void setMinute(int value){    
    setTime(1,value);
}

void setHour(int value){    
    setTime(2,value);
}

void setDay(int value){    
    setTime(3,value);
}

void setMonth(int value){    
    setTime(4,value);
}

void setYear(int value){    
    setTime(5,value);
}


void setTime(int select, int value){

    rtci2c_context *ctx = rtci2c_init(RTCI2C_DEVICE_PCF8563, DEVICE_I2C_ADDRESS, &config);
        if(NULL == ctx)
        {
            ESP_LOGE(TAG, "Initialization failed");
        }
        else
        {
            struct tm t;
            
            //if (CLOCK_INTERFACE_DEBUG) ESP_LOGE(TAG, "%d ", t.tm_hour);

            if(!rtci2c_get_datetime(ctx, &t))
            {
                ESP_LOGE(TAG, "Date/tate query failed");
            }
            else
            {
                //ESP_LOGE(TAG, "Current: %02u/%02u/20%02u %02u:%02u:%02u",
                //t.tm_mday, t.tm_mon, t.tm_year, t.tm_hour, t.tm_min, t.tm_sec);
            }


            switch (select){
                case 0 : t.tm_sec = value;
                        break;
                case 1 : t.tm_min = value;
                        break; 
                case 2 : t.tm_hour = value;
                        break;
                case 3 : t.tm_mday = value;
                        break;    
                case 4 : t.tm_mon = value;
                        break;
                case 5 : t.tm_year = value;
                        break;                   
                default : break;
            }

            rtci2c_set_datetime(ctx, &t);         
            rtci2c_deinit(ctx);        
        }
}




void initClock (void){

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default() );

    #if RTCI2C_LIBRARY_I2C_BUS_INIT
    /* Allow the rtci2c library to initialize the i2c bus */
    config.port = ESP_I2C_PORT;
    config.pin_sda = ESP_I2C_SDA;
    config.pin_scl = ESP_I2C_SCL;

    #else
    /* Initialize the i2c bus the way we want. Optionally keep the "bus"
        pointer to allow the use of the same bus instance for other i2c
        device communication. */
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = ESP_I2C_PORT, 
        .sda_io_num = ESP_I2C_SDA,
        .scl_io_num = ESP_I2C_SCL,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,      
    };
    if(i2c_new_master_bus(&bus_cfg, &i2c_bus) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize I2C bus");
    }
    config.bus = &i2c_bus;
    #endif

}

void clock_task(void *arg){
    for(;;) {
        rtci2c_context *ctx = rtci2c_init(RTCI2C_DEVICE_PCF8563, DEVICE_I2C_ADDRESS, &config);
        if(NULL == ctx)
        {
            ESP_LOGE(TAG, "Initialization failed");
        }
        else
        {
            struct tm t;

            for(int i = 0; i < 100; ++i)
            {
                if(!rtci2c_get_datetime(ctx, &t))
                {
                    ESP_LOGE(TAG, "Date/tate query failed");
                }
                else
                {
                    ESP_LOGI(TAG, "Current: %02u/%02u/20%02u %02u:%02u:%02u",
                    t.tm_mday, t.tm_mon, t.tm_year, t.tm_hour, t.tm_min, t.tm_sec);
                }
                vTaskDelay(pdMS_TO_TICKS(5000));
            }
            rtci2c_deinit(ctx);        
        }
    }
}