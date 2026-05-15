#include "button_reset.h"

#include "app_config.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "button_reset";

static int64_t s_press_start_us = 0;
static void (*s_reset_cb)(void) = NULL;

static void IRAM_ATTR button_isr_handler(void *arg) {
    int level = gpio_get_level((gpio_num_t)(uintptr_t)arg);
    int64_t now = esp_timer_get_time();
    if (level == 0) {
        s_press_start_us = now;
    } else if (s_press_start_us > 0) {
        int64_t diff_ms = (now - s_press_start_us) / 1000;
        s_press_start_us = 0;
        if (diff_ms >= APP_BUTTON_LONG_PRESS_MS && s_reset_cb) {
            s_reset_cb();
        }
    }
}

void button_reset_init(void (*reset_cb)(void)) {
    s_reset_cb = reset_cb;

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << APP_BUTTON_RESET_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(APP_BUTTON_RESET_GPIO, button_isr_handler,
                                         (void *)(uintptr_t)APP_BUTTON_RESET_GPIO));
    ESP_LOGI(TAG, "button reset enabled gpio=%d long_press_ms=%d", APP_BUTTON_RESET_GPIO,
             APP_BUTTON_LONG_PRESS_MS);
}
