#pragma once

#include "esp_err.h"

esp_err_t provision_manager_init(void);
esp_err_t provision_manager_start_if_needed(void);
void provision_manager_reset_and_restart(void);
