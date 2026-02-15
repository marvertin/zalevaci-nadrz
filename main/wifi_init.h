#ifndef WIFI_INIT_H
#define WIFI_INIT_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializuje WiFi stanici a připojí se k síti
 * 
 * @return ESP_OK při úspěchu, jinak chybový kód
 */
esp_err_t wifi_init_sta(const char *ssid, const char *password);

/**
 * @brief Inicializuje WiFi access point pro konfiguraci
 *
 * @param ap_ssid SSID access pointu
 * @param ap_password Heslo AP (prázdný řetězec = open AP)
 * @return ESP_OK při úspěchu, jinak chybový kód
 */
esp_err_t wifi_init_ap(const char *ap_ssid, const char *ap_password);

/**
 * @brief Čeká na připojení k WiFi
 * 
 * @param timeout_ms Timeout v milisekundách (0 = čekat nekonečně)
 * @return true pokud je připojeno, false při timeoutu
 */
bool wifi_wait_connected(uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif // WIFI_INIT_H
