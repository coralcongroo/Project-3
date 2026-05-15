# Android Integration Plan

## 推荐库
- Espressif 官方：`esp-idf-provisioning-android`

## BLE 权限
- Android 12+：`BLUETOOTH_SCAN`、`BLUETOOTH_CONNECT`、`ACCESS_FINE_LOCATION`（视机型/系统策略）。
- Android 11-：`ACCESS_FINE_LOCATION` + 蓝牙权限。

## 扫码配网流程
1. 扫描二维码，解析字段（见 `qr-code-format.md`）。
2. 按 `name` 扫描并连接 BLE。
3. 使用 `security` + `pop` 发起会话。
4. 下发 Wi-Fi。
5. 轮询 provisioning 状态。
6. （可选）发送 `custom-data`（bind_token、region等）。
7. 展示结果并引导设备绑定云端。

## 配网 UI 建议
- 步骤型 UI：扫描设备 -> 安全认证 -> 下发 Wi-Fi -> 连接验证 -> 绑定完成。
- 状态映射使用统一状态机枚举。
- 失败弹窗使用统一错误码文案。

## custom endpoint 对接建议
- endpoint 名称固定 `custom-data`。
- payload 采用 JSON UTF-8。
- 建议字段：`product_id/device_id/bind_token/region/mqtt_host/user_id`。

## 预留
- TODO(Security2): 引入 username/password(SRP) 流程。
- TODO(SoftAP): BLE 失败时支持 SoftAP 兜底。
