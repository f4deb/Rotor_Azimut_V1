# esp-idf component
if(IDF_TARGET)
   idf_component_register(SRCS "lib/sensori2c.c" "lib/LSM303DLHC.c" "../rtci2c/lib/esp-idf.c"
                          INCLUDE_DIRS "include"
                                       "../rtci2c/include"
                                       "../rtci2c/lib"
                          PRIV_INCLUDE_DIRS "lib" "include/sensori2c"
                          PRIV_REQUIRES "driver" "esp_timer")
   return()
endif()




