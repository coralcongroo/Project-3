#include "provision_manager.h"

#include "app_config.h"
#include "app_events.h"
#include "custom_endpoint.h"
#include "device_info.h"
#include "esp_check.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_storage.h"
#include "wifi_manager.h"
#include "wifi_provisioning/manager.h"
#include "wifi_provisioning/scheme_ble.h"

static const char *TAG = "prov_mgr";

static void prov_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id,
                               void *event_data) {
    (void)arg;
    (void)event_data;
    if (event_base == WIFI_PROV_EVENT) {
        switch (event_id) {
        case WIFI_PROV_START:
            app_events_set_state(APP_STATE_BLE_ADVERTISING);
            break;
        case WIFI_PROV_CRED_RECV:
            app_events_set_state(APP_STATE_WIFI_CONFIG_RECEIVED);
            break;
        case WIFI_PROV_CRED_SUCCESS:
            app_events_set_state(APP_STATE_WIFI_CONNECTED);
            nvs_storage_set_wifi_provisioned(true);
            break;
        case WIFI_PROV_CRED_FAIL:
            app_events_set_state(APP_STATE_PROVISION_FAILED);
            break;
        case WIFI_PROV_END:
            app_events_set_state(APP_STATE_PROVISION_DONE);
            wifi_prov_mgr_deinit();
            break;
        default:
            break;
        }
    }
}

esp_err_t provision_manager_init(void) {
    wifi_prov_mgr_config_t config = {
        .scheme = wifi_prov_scheme_ble,
        .scheme_event_handler = WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM,
    };
    ESP_RETURN_ON_ERROR(wifi_prov_mgr_init(config), TAG, "prov init failed");
    ESP_RETURN_ON_ERROR(esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, prov_event_handler,
                                                   NULL),
                        TAG, "prov event handler failed");
    return ESP_OK;
}

esp_err_t provision_manager_start_if_needed(void) {
    bool provisioned = false;
    wifi_prov_mgr_is_provisioned(&provisioned);
    app_events_set_state(APP_STATE_WAITING_FOR_PROVISION);

    if (provisioned || nvs_storage_get_wifi_provisioned()) {
        ESP_LOGI(TAG, "already provisioned; connect Wi-Fi");
        app_events_set_state(APP_STATE_WIFI_CONNECTING);
        return wifi_manager_connect();
    }

    char service_name[16] = {0};
    device_info_build_prov_name(service_name, sizeof(service_name));

    ESP_LOGI(TAG, "start BLE provisioning name=%s security=%d", service_name, APP_PROV_SECURITY);
    app_events_set_state(APP_STATE_SECURITY_HANDSHAKE);

    ESP_RETURN_ON_ERROR(custom_endpoint_register(), TAG, "custom endpoint failed");
    ESP_RETURN_ON_ERROR(wifi_prov_mgr_start_provisioning(APP_PROV_SECURITY, (const void *)APP_PROV_POP,
                                                         service_name, NULL),
                        TAG, "start provisioning failed");

    return ESP_OK;
}

void provision_manager_reset_and_restart(void) {
    ESP_LOGW(TAG, "reset provisioning and restart");
    ESP_ERROR_CHECK_WITHOUT_ABORT(wifi_manager_reset_provisioning());
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_storage_set_wifi_provisioned(false));
    ESP_ERROR_CHECK_WITHOUT_ABORT(wifi_prov_mgr_reset_sm_state_for_reprovision());
    ESP_ERROR_CHECK_WITHOUT_ABORT(provision_manager_start_if_needed());
}
