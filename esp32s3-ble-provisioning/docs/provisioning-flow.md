# Provisioning Flow

## 状态机
`IDLE -> WAITING_FOR_PROVISION -> BLE_ADVERTISING -> BLE_CONNECTED -> SECURITY_HANDSHAKE -> WIFI_CONFIG_RECEIVED -> WIFI_CONNECTING -> WIFI_CONNECTED -> CLOUD_BINDING -> PROVISION_DONE`

失败路径：`* -> PROVISION_FAILED`。

## 时序（Phase-1）
1. 设备上电，检查是否已配网。
2. 未配网：启动 BLE provisioning，广播 `PROV_XXXXXX`。
3. Python/Android 扫描并连接。
4. 执行 Security1 + PoP。
5. 下发 SSID/Password。
6. 设备连接 Wi-Fi，成功则停止 provisioning。
7. 可选发送 `custom-data`（JSON），设备存入 NVS。
8. 重启后自动连网，不再进入 provisioning。
9. 长按按键后清空配置并回到 provisioning。

## 状态映射建议
- Python CLI 输出状态字符串。
- Android UI 同步映射为步骤条 + 错误提示（参考 `error-codes.md`）。
