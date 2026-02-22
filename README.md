# zalevaci-nadrz

## Struktura mqtt topiků.

```
home/water_tank/
 ├── state/
 │    ├── volume_l
 │    ├── flow_l_min
 │    ├── total_pumped_l
 │    ├── temp_water_c
 │    ├── temp_shaft_c
 │    ├── pressure_bar
 │    ├── filter_delta_bar
 │    └── pump/
 │         ├── running
 │         ├── power_w
 │         ├── current_a
 │         ├── voltage_v
 │         └── energy_kwh
 │
 ├── diag/
 │    ├── wifi_rssi_dbm
 │    ├── uptime_s
 │    ├── free_heap_b
 │    └── mqtt_reconnects
 │
 ├── event/
 │    ├── reboot_reason
 │    └── reboot_counter
 │
 ├── status
 │
 ├── cmd/
 │
 └── debug/
      ├── raw/
      └── intermediate/
```      
home/water_tank/state/heartbeat

## Publikační pravidla

| Kategorie | QoS | Retain |
| --- | ---: | :---: |
| state | 1 | ano |
| status | 1 | ano |
| event | 1 | ne |
| diag | 1 | ano |
| debug | 0 | ne |
| cmd | 1 | ne |

## Příkazy přes MQTT


* home/water_tank/cmd/reboot
* home/water_tank/cmd/reset_total
* home/water_tank/cmd/service_mode

## Poslat last will.

esp_mqtt_client_config_t mqtt_cfg = {
    .broker.address.uri = "mqtt://mqtt.home.arpa",
    .credentials.username = "esp32_tank",
    .credentials.authentication.password = "tajne",
    .session.last_will.topic = "home/water_tank/status",
    .session.last_will.msg = "offline",
    .session.last_will.qos = 1,
    .session.last_will.retain = 1,
};

