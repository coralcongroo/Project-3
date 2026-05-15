#pragma once

#include "esp_err.h"
#include <stdbool.h>
#include <stddef.h>

esp_err_t nvs_storage_init(void);
esp_err_t nvs_storage_save_custom_json(const char *json);
esp_err_t nvs_storage_load_custom_json(char *out, size_t out_size);
esp_err_t nvs_storage_clear_all(void);
esp_err_t nvs_storage_set_wifi_provisioned(bool provisioned);
bool nvs_storage_get_wifi_provisioned(void);
