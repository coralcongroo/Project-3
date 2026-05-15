#pragma once

#include "esp_err.h"
#include <stdbool.h>

esp_err_t wifi_manager_init(void);
esp_err_t wifi_manager_connect(void);
bool wifi_manager_is_provisioned(void);
esp_err_t wifi_manager_reset_provisioning(void);
