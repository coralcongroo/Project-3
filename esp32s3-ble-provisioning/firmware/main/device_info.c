#include "device_info.h"

#include "esp_mac.h"
#include <stdio.h>

void device_info_build_prov_name(char *out_name, size_t out_size) {
    uint8_t mac[6] = {0};
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    snprintf(out_name, out_size, "PROV_%02X%02X%02X", mac[3], mac[4], mac[5]);
}
