# Architecture

- **firmware/**：ESP-IDF 设备端。
  - `app_main.c` 负责启动顺序。
  - `provision_manager.*` 封装 Wi-Fi Provisioning Manager（BLE + Security1 + PoP）。
  - `wifi_manager.*` 管理 STA 初始化/连接状态。
  - `custom_endpoint.*` 注册并处理 `custom-data` endpoint。
  - `app_events.*` 统一状态机和状态通知。
  - `nvs_storage.*` 保存业务配置（custom JSON）。
  - `button_reset.*` 长按清空配网。
  - `led_status.*` LED 状态接口（占位）。
  - `device_info.*` 生成 `PROV_XXXXXX` 设备名。

- **tools/python-provisioner/**：Python 3.10+ CLI 工具。
  - `scan/provision/status/custom/parse-qr` 命令。
  - BLE 基于 `bleak`。
  - 协议模型与错误码与固件/Android文档统一。

- **docs/**：时序、二维码、错误码、Android 接入、量产说明。

设计原则：
1. 协议尽量沿用 ESP-IDF 官方 provisioning 机制，避免 Python 私有协议。
2. Security0 禁止作为正式方案。
3. 在模块边界预留 Security2、SoftAP、Android 扩展点。
