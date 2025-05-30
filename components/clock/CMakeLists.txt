idf_component_register(SRCS "clockInterface.c" "clock.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
INCLUDE_DIRS "include" 
            "../uartCommand/include"
            "../charUtils/include"
            "../rtci2c/include"
            "../../../esp/v5.4/esp-idf/components/esp_driver_i2c/include"
            "../../../esp/v5.4/esp-idf/components/nvs_flash/include"
            "../../../esp/v5.4/esp-idf/components/esp_event/include"
            "../../../esp/v5.4/esp-idf/components/esp_partition/include"
        
)