#include "nvs_storage.h"

#include "esp_check.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *TAG = "nvs_storage";
static const char *NS_APP = "app_cfg";
static const char *KEY_CUSTOM = "custom_json";
static const char *KEY_WIFI_PROV = "wifi_prov";

esp_err_t nvs_storage_init(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err;
}

esp_err_t nvs_storage_save_custom_json(const char *json) {
    if (json == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    nvs_handle_t handle;
    ESP_RETURN_ON_ERROR(nvs_open(NS_APP, NVS_READWRITE, &handle), TAG, "nvs open failed");
    esp_err_t err = nvs_set_str(handle, KEY_CUSTOM, json);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

esp_err_t nvs_storage_load_custom_json(char *out, size_t out_size) {
    if (out == NULL || out_size == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    nvs_handle_t handle;
    ESP_RETURN_ON_ERROR(nvs_open(NS_APP, NVS_READONLY, &handle), TAG, "nvs open failed");
    size_t required = out_size;
    esp_err_t err = nvs_get_str(handle, KEY_CUSTOM, out, &required);
    nvs_close(handle);
    return err;
}

esp_err_t nvs_storage_clear_all(void) {
    nvs_handle_t handle;
    ESP_RETURN_ON_ERROR(nvs_open(NS_APP, NVS_READWRITE, &handle), TAG, "nvs open failed");
    esp_err_t err = nvs_erase_all(handle);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

esp_err_t nvs_storage_set_wifi_provisioned(bool provisioned) {
    nvs_handle_t handle;
    ESP_RETURN_ON_ERROR(nvs_open(NS_APP, NVS_READWRITE, &handle), TAG, "nvs open failed");
    esp_err_t err = nvs_set_u8(handle, KEY_WIFI_PROV, provisioned ? 1 : 0);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

bool nvs_storage_get_wifi_provisioned(void) {
    nvs_handle_t handle;
    uint8_t val = 0;
    if (nvs_open(NS_APP, NVS_READONLY, &handle) != ESP_OK) {
        return false;
    }
    esp_err_t err = nvs_get_u8(handle, KEY_WIFI_PROV, &val);
    nvs_close(handle);
    return err == ESP_OK && val == 1;
}
