idf_component_register(SRCS "Oled.c" "../I2c/I2c.c" "OledInterface.c"
                    INCLUDE_DIRS "include"
                    "../../components/I2c/include"
                    
                    "/home/f4deb/RotorV1A/managed_components/espressif__esp_lvgl_port/include"
                    "/home/f4deb/RotorV1A/managed_components/lvgl__lvgl"

                    "../../../esp/v5.4/esp-idf/components/esp_driver_i2c/include"
                    "../../../esp/v5.4/esp-idf/components/nvs_flash/include"
                    "../../../esp/v5.4/esp-idf/components/log/include"
                    "../../../esp/v5.4/esp-idf/components/esp_event/include"
                    "../../../esp/v5.4/esp-idf/components/esp_partition/include"
                    "../../../esp/v5.4/esp-idf/components/esp_driver_spi/include"
                    "../../../esp/v5.4/esp-idf/components/esp_lcd/include"
                    )