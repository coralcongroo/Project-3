#include "custom_endpoint.h"

#include "app_config.h"
#include "esp_check.h"
#include "esp_log.h"
#include "nvs_storage.h"
#include "wifi_provisioning/manager.h"
#include <stdlib.h>
#include <string.h>

static const char *TAG = "custom_ep";

static esp_err_t custom_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                     uint8_t **outbuf, ssize_t *outlen, void *priv_data) {
    (void)session_id;
    (void)priv_data;
    if (inbuf == NULL || inlen <= 0 || outbuf == NULL || outlen == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    char *json = calloc(1, (size_t)inlen + 1);
    if (json == NULL) {
        return ESP_ERR_NO_MEM;
    }
    memcpy(json, inbuf, (size_t)inlen);

    ESP_LOGI(TAG, "custom-data recv: %s", json);
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_storage_save_custom_json(json));

    *outbuf = (uint8_t *)strdup(json);
    *outlen = (ssize_t)strlen(json);
    free(json);
    return *outbuf ? ESP_OK : ESP_ERR_NO_MEM;
}

esp_err_t custom_endpoint_register(void) {
    ESP_RETURN_ON_ERROR(wifi_prov_mgr_endpoint_create(APP_CUSTOM_ENDPOINT_NAME), TAG,
                        "endpoint create failed");
    return wifi_prov_mgr_endpoint_register(APP_CUSTOM_ENDPOINT_NAME, custom_data_handler, NULL);
}
