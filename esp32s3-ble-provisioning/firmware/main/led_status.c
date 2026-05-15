#include "led_status.h"

#include "esp_log.h"

static const char *TAG = "led_status";

void led_status_init(void) {
    ESP_LOGI(TAG, "LED status interface initialized (placeholder)");
}

void led_status_set_by_state(app_state_t state) {
    ESP_LOGI(TAG, "LED update by state=%d (placeholder)", (int)state);
}
