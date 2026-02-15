#ifdef __cplusplus
extern "C" {
#endif

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"

#ifdef __cplusplus
}
#endif

#include "pins.h"
#include "sensor_events.h"

#define TAG "FLOW_DEMO"

// sdílený counter z ISR
static volatile uint32_t pulse_count = 0;

// ISR handler
static void IRAM_ATTR flow_isr_handler(void *arg) {
    pulse_count += 1;
}

static void pocitani_pulsu(void *pvParameters)
{
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(200));   // měřím 1× za sekundu

        sensor_event_t event = {
            .type = SENSOR_EVENT_FLOW,
            .timestamp_us = esp_timer_get_time(),
            .data = {
                .flow = {
                    .pulse_count = pulse_count,
                },
            },
        };

        if (!sensor_events_publish(&event, pdMS_TO_TICKS(20))) {
            ESP_LOGW(TAG, "Fronta sensor eventu je plna, prutok zahozen");
        }
    }
}

void prutokomer_demo_init(void)
{
    // --- Nastavení GPIO pro flow senzor ---
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << FLOW_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(FLOW_GPIO, flow_isr_handler, NULL);

    ESP_LOGI(TAG, "Startuji měření pulzů...");

    xTaskCreate(pocitani_pulsu, "pocitani_pulsu", 2048, NULL, 1, NULL);
}
