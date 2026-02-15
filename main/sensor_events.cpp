#include "sensor_events.h"

#include "esp_log.h"
#include <freertos/queue.h>

static const char *TAG = "SENSOR_EVENTS";
static QueueHandle_t s_sensor_events_queue = nullptr;

void sensor_events_init(size_t queue_length)
{
    if (s_sensor_events_queue != nullptr) {
        return;
    }

    s_sensor_events_queue = xQueueCreate(queue_length, sizeof(sensor_event_t));
    if (s_sensor_events_queue == nullptr) {
        ESP_LOGE(TAG, "Nelze vytvorit frontu sensor eventu");
        abort();
    }
}

bool sensor_events_publish(const sensor_event_t *event, TickType_t timeout)
{
    if (s_sensor_events_queue == nullptr || event == nullptr) {
        return false;
    }

    return xQueueSend(s_sensor_events_queue, event, timeout) == pdTRUE;
}

bool sensor_events_receive(sensor_event_t *event, TickType_t timeout)
{
    if (s_sensor_events_queue == nullptr || event == nullptr) {
        return false;
    }

    return xQueueReceive(s_sensor_events_queue, event, timeout) == pdTRUE;
}
