idf_component_register(SRCS "clockInterface.c" "clock.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
INCLUDE_DIRS "include" 
            "../uartCommand/include"
            "../charUtils/include"
            "../rtci2c/include"
            "$ENV{IDF_PATH}/components/esp_driver_i2c/include"
            "$ENV{IDF_PATH}/components/nvs_flash/include"
            "$ENV{IDF_PATH}/components/esp_event/include"
            "$ENV{IDF_PATH}/components/esp_partition/include"
        
)