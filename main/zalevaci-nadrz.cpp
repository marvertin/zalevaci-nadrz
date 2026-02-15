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
#include "restart_info.h"
#include "sensor_events.h"
#include "sensor_dispatch.h"

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

    app_restart_info_t restart_info = {};
    ESP_ERROR_CHECK(app_restart_info_update_and_load(&restart_info));

    config_webapp_restart_info_t webapp_restart_info = {
        .boot_count = restart_info.boot_count,
        .last_reason = static_cast<int32_t>(restart_info.last_reason),
        .last_restart_unix = restart_info.last_restart_unix,
    };

    esp_err_t config_result = config_webapp_start(
        "app_cfg",
        config_groups,
        sizeof(config_groups) / sizeof(config_groups[0]),
        80,
        &webapp_restart_info);
    if (config_result != ESP_OK) {
        ESP_LOGW("main", "Config web app se nepodarilo spustit: %s", esp_err_to_name(config_result));
    }
    
    // Inicializace MQTT - upravte URI podle vaší Home Assistant instance
    ESP_ERROR_CHECK(mqtt_init("mqtt://mqtt:1883"));
    
    lcd_init(); // Inicializace LCD před spuštěním ostatních demo úloh, aby mohly ihned zobrazovat informace

    sensor_events_init(32);
    sensor_dispatch_start();
    
    // initialize sensor producer tasks
    prutokomer_demo_init();

    // vytvoření paralelních tasků
    blikaniled_init();
    // lcd_demo_init();
    teplota_demo_init();
    hladina_demo_init();
}
