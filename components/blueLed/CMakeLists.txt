idf_component_register(SRCS "blueLedInterface.c" "blueLed.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        "/home/f4deb/esp/v5.4/esp-idf/components/esp_event/include"
                        "/home/f4deb/esp/v5.4/esp-idf/components/esp_driver_gpio/include")