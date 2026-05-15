# Manufacturing Guide

## 量产信息生成建议
1. `device_id`：由 MAC 后 3 字节（HEX）或工厂流水号生成。
2. `pop`：每设备唯一随机值（至少 6 位，建议更长）。
3. `product_id`：按机型固定。
4. 生成二维码 JSON 并打印标签。

## 推荐流程
1. 烧录固件。
2. 产测工具读取 MAC -> 生成 `device_id`、`name=PROV_XXXXXX`。
3. 写入出厂基础参数（如 product_id）。
4. 生成并校验二维码。
5. 抽检 Python CLI 扫描、配网、状态查询。

## 标签建议
- 明文字段：`name`, `device_id`, `product_id`。
- 隐私字段（`pop`）按产品策略决定是否明文暴露。

## 安全建议
- PoP 不应使用公共默认值。
- 保留升级 Security2 的服务端/产线字段。
