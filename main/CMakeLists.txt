idf_component_register(SRCS "zalevaci-nadrz.c" "blikaniled.c" "lcd-demo.c" "prutokomer-demo.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_gpio
                    PRIV_REQUIRES esp_timer)
