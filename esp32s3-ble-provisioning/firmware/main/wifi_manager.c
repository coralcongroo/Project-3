#include "wifi_manager.h"

#include "esp_check.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"

static const char *TAG = "wifi_manager";

esp_err_t wifi_manager_init(void) {
    ESP_RETURN_ON_ERROR(esp_netif_init(), TAG, "netif init failed");
    ESP_RETURN_ON_ERROR(esp_event_loop_create_default(), TAG, "event loop failed");
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_RETURN_ON_ERROR(esp_wifi_init(&cfg), TAG, "wifi init failed");
    ESP_RETURN_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), TAG, "set mode failed");
    ESP_RETURN_ON_ERROR(esp_wifi_start(), TAG, "wifi start failed");
    return ESP_OK;
}

bool wifi_manager_is_provisioned(void) {
    wifi_config_t wifi_cfg = {0};
    if (esp_wifi_get_config(WIFI_IF_STA, &wifi_cfg) != ESP_OK) {
        return false;
    }
    return wifi_cfg.sta.ssid[0] != '\0';
}

esp_err_t wifi_manager_connect(void) {
    ESP_LOGI(TAG, "connecting to saved Wi-Fi config");
    return esp_wifi_connect();
}

esp_err_t wifi_manager_reset_provisioning(void) {
    ESP_LOGW(TAG, "resetting Wi-Fi provisioning state");
    return esp_wifi_restore();
}
