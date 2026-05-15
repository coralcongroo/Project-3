# ESP32-S3 BLE Wi-Fi Provisioning

## 项目目标
基于 ESP32-S3 + ESP-IDF 5.x，使用官方 Wi-Fi Provisioning / Protocomm 实现 BLE 配网，Python CLI 用于前期调试和产测，协议保持与后续 Android 官方库兼容。

## 当前阶段能力（Phase-1）
- 设备未配网自动进入 BLE provisioning（Security1 + PoP）。
- BLE 设备名：`PROV_XXXXXX`（MAC 后 3 字节）。
- 收到 Wi-Fi 后连接并保存；成功后停止 BLE provisioning。
- 长按按键清除配网并重新进入 provisioning。
- 自定义 endpoint（`custom-data`）支持保存 JSON 字符串并回显。
- 统一状态机、错误码、二维码格式文档。

## 仓库结构
详见：`docs/architecture.md`

## 快速开始

### 1) 固件编译烧录
```bash
cd firmware
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

### 2) Python CLI 安装
```bash
cd tools/python-provisioner
python3 -m venv .venv
source .venv/bin/activate
pip install -e .
```

### 3) Python CLI 使用
```bash
provisioner scan
provisioner parse-qr --qr '{"ver":"v1","name":"PROV_A1B2C3","transport":"ble","security":1,"pop":"123456","product_id":"esp32s3_demo","device_id":"A1B2C3"}'
provisioner provision --name PROV_A1B2C3 --ssid MyWiFi --password 12345678 --pop 123456
provisioner status --name PROV_A1B2C3 --pop 123456
provisioner custom --name PROV_A1B2C3 --pop 123456 --json '{"bind_token":"token","region":"cn"}'
```

## BLE 配网流程
详见：`docs/provisioning-flow.md`

## Android 后续接入计划
详见：`docs/android-integration.md`（基于 `esp-idf-provisioning-android`）。

## 扩展 TODO
- TODO(Security2): 升级到 Security2（username + SRP）。
- TODO(SoftAP): 增加 SoftAP fallback。
- TODO(Android): 以同一 QR 字段与 custom endpoint 协议对接 Android App。
