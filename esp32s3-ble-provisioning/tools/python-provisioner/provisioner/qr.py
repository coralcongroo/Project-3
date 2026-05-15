from __future__ import annotations

import json

from .errors import ProvisionError
from .models import ErrorCode, QrPayload

_REQUIRED_FIELDS = ["ver", "name", "transport", "security", "pop", "product_id", "device_id"]


def parse_qr_json(raw: str) -> QrPayload:
    try:
        data = json.loads(raw)
    except json.JSONDecodeError as exc:
        raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, f"invalid qr json: {exc}") from exc

    missing = [field for field in _REQUIRED_FIELDS if field not in data]
    if missing:
        raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, f"qr missing fields: {','.join(missing)}")

    return QrPayload(
        ver=str(data["ver"]),
        name=str(data["name"]),
        transport=str(data["transport"]),
        security=int(data["security"]),
        pop=str(data["pop"]),
        product_id=str(data["product_id"]),
        device_id=str(data["device_id"]),
        username=data.get("username") or None,
    )
