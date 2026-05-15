# QR Code Format

统一二维码 JSON：

```json
{
  "ver": "v1",
  "name": "PROV_A1B2C3",
  "transport": "ble",
  "security": 1,
  "pop": "123456",
  "product_id": "esp32s3_demo",
  "device_id": "A1B2C3",
  "username": "optional_for_security2"
}
```

字段说明：
- `ver`：二维码版本。
- `name`：BLE 广播设备名。
- `transport`：`ble`（后续可扩展 `softap`）。
- `security`：1=Security1，2=Security2（预留）。
- `pop`：PoP。
- `product_id`：产品型号标识。
- `device_id`：设备唯一短标识。
- `username`：Security2 预留字段。

兼容性要求：Python 与 Android 使用同一字段，不新增私有必填字段。
