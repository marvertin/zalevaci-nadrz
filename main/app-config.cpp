#include "app-config.h"

static const config_item_t APP_CORE_CONFIG_ITEMS[] = {
    {
        .key = "interval_s",
        .label = "Interval měření [s]",
        .description = "Perioda měření a publikace hodnot.",
        .type = CONFIG_VALUE_INT32,
        .default_string = nullptr,
        .default_int = 30,
        .default_float = 0.0f,
        .default_bool = false,
        .max_string_len = 0,
        .min_int = 5,
        .max_int = 3600,
        .min_float = 0.0f,
        .max_float = 0.0f,
    },
    {
        .key = "tepl_max",
        .label = "Max. teplota [°C]",
        .description = "Prahová teplota pro alarm nebo ochranu.",
        .type = CONFIG_VALUE_FLOAT,
        .default_string = nullptr,
        .default_int = 0,
        .default_float = 35.0f,
        .default_bool = false,
        .max_string_len = 0,
        .min_int = 0,
        .max_int = 0,
        .min_float = -20.0f,
        .max_float = 90.0f,
    },
    {
        .key = "auto_mode",
        .label = "Automatický režim",
        .description = "Zapíná automatické vyhodnocení závlahy.",
        .type = CONFIG_VALUE_BOOL,
        .default_string = nullptr,
        .default_int = 0,
        .default_float = 0.0f,
        .default_bool = true,
        .max_string_len = 0,
        .min_int = 0,
        .max_int = 0,
        .min_float = 0.0f,
        .max_float = 0.0f,
    },
    {
        .key = "mqtt_topic",
        .label = "MQTT topic",
        .description = "Kořenový topic pro publikaci dat zařízení.",
        .type = CONFIG_VALUE_STRING,
        .default_string = "zalevaci-nadrz",
        .default_int = 0,
        .default_float = 0.0f,
        .default_bool = false,
        .max_string_len = 63,
        .min_int = 0,
        .max_int = 0,
        .min_float = 0.0f,
        .max_float = 0.0f,
    },
};

config_group_t app_config_get_config_group(void)
{
    config_group_t group = {
        .items = APP_CORE_CONFIG_ITEMS,
        .item_count = sizeof(APP_CORE_CONFIG_ITEMS) / sizeof(APP_CORE_CONFIG_ITEMS[0]),
    };
    return group;
}
