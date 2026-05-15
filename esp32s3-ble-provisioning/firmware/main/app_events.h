#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_WAITING_FOR_PROVISION,
    APP_STATE_BLE_ADVERTISING,
    APP_STATE_BLE_CONNECTED,
    APP_STATE_SECURITY_HANDSHAKE,
    APP_STATE_WIFI_CONFIG_RECEIVED,
    APP_STATE_WIFI_CONNECTING,
    APP_STATE_WIFI_CONNECTED,
    APP_STATE_CLOUD_BINDING,
    APP_STATE_PROVISION_DONE,
    APP_STATE_PROVISION_FAILED,
} app_state_t;

void app_events_init(void);
void app_events_set_state(app_state_t state);
app_state_t app_events_get_state(void);
const char *app_events_state_to_str(app_state_t state);

#ifdef __cplusplus
}
#endif
