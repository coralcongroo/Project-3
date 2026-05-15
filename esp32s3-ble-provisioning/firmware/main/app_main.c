#include "app_events.h"
#include "button_reset.h"
#include "esp_err.h"
#include "esp_log.h"
#include "led_status.h"
#include "nvs_storage.h"
#include "provision_manager.h"
#include "wifi_manager.h"

static const char *TAG = "app_main";

void app_main(void) {
    ESP_ERROR_CHECK(nvs_storage_init());
    app_events_init();
    led_status_init();

    ESP_ERROR_CHECK(wifi_manager_init());
    ESP_ERROR_CHECK(provision_manager_init());

    button_reset_init(provision_manager_reset_and_restart);

    ESP_ERROR_CHECK(provision_manager_start_if_needed());

    ESP_LOGI(TAG, "application started");
}
