idf_component_register(
    SRCS
        "app_main.c"
        "app_events.c"
        "provision_manager.c"
        "wifi_manager.c"
        "custom_endpoint.c"
        "device_info.c"
        "nvs_storage.c"
        "button_reset.c"
        "led_status.c"
    INCLUDE_DIRS "."
    REQUIRES nvs_flash esp_wifi wifi_provisioning bt driver
)
