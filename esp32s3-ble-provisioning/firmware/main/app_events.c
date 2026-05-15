#include "app_events.h"

#include "esp_log.h"

static const char *TAG = "app_events";
static app_state_t s_state = APP_STATE_IDLE;

void app_events_init(void) {
    s_state = APP_STATE_IDLE;
    ESP_LOGI(TAG, "state=%s", app_events_state_to_str(s_state));
}

void app_events_set_state(app_state_t state) {
    s_state = state;
    ESP_LOGI(TAG, "state=%s", app_events_state_to_str(s_state));
}

app_state_t app_events_get_state(void) { return s_state; }

const char *app_events_state_to_str(app_state_t state) {
    switch (state) {
    case APP_STATE_IDLE:
        return "IDLE";
    case APP_STATE_WAITING_FOR_PROVISION:
        return "WAITING_FOR_PROVISION";
    case APP_STATE_BLE_ADVERTISING:
        return "BLE_ADVERTISING";
    case APP_STATE_BLE_CONNECTED:
        return "BLE_CONNECTED";
    case APP_STATE_SECURITY_HANDSHAKE:
        return "SECURITY_HANDSHAKE";
    case APP_STATE_WIFI_CONFIG_RECEIVED:
        return "WIFI_CONFIG_RECEIVED";
    case APP_STATE_WIFI_CONNECTING:
        return "WIFI_CONNECTING";
    case APP_STATE_WIFI_CONNECTED:
        return "WIFI_CONNECTED";
    case APP_STATE_CLOUD_BINDING:
        return "CLOUD_BINDING";
    case APP_STATE_PROVISION_DONE:
        return "PROVISION_DONE";
    case APP_STATE_PROVISION_FAILED:
        return "PROVISION_FAILED";
    default:
        return "UNKNOWN";
    }
}
