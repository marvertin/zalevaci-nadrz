#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_rom_sys.h"
#include <stdio.h>
#include "tm1637.h"
#include "i2cdev.h"
#include "pcf8574.h"

#include "pins.h"
#include "blikaniled.h"
#include "lcd-demo.h"
#include "prutokomer-demo.h"
#include "teplota-demo.h"
#include "hladina-demo.h"
#include "app-config.h"

#include "lcd.h"
#include "wifi_init.h"
#include "mqtt_init.h"
#include "config_webapp.h"

extern "C" {
    void cpp_app_main(void);
}

void cpp_app_main(void)
{
    // Inicializace WiFi
    ESP_ERROR_CHECK(wifi_init_sta());
    
    // Čekáme na připojení (timeout 10 sekund)
    wifi_wait_connected(10000);

    const config_group_t config_groups[] = {
        app_config_get_config_group(),
        hladina_demo_get_config_group(),
    };

    esp_err_t config_result = config_webapp_start(
        "app_cfg",
        config_groups,
        sizeof(config_groups) / sizeof(config_groups[0]),
        80);
    if (config_result != ESP_OK) {
        ESP_LOGW("main", "Config web app se nepodarilo spustit: %s", esp_err_to_name(config_result));
    }
    
    // Inicializace MQTT - upravte URI podle vaší Home Assistant instance
    ESP_ERROR_CHECK(mqtt_init("mqtt://192.168.2.108:1883"));
    
    lcd_init(); // Inicializace LCD před spuštěním ostatních demo úloh, aby mohly ihned zobrazovat informace
    
    // initialize flowmeter + display tasks
    prutokomer_demo_init();

    // vytvoření paralelních tasků
    blikaniled_init();
    // lcd_demo_init();
    teplota_demo_init();
    hladina_demo_init();
}
