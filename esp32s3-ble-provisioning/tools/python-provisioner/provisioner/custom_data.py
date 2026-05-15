from __future__ import annotations

import json

from .errors import ProvisionError
from .models import ErrorCode


def normalize_custom_data(raw_json: str) -> str:
    try:
        payload = json.loads(raw_json)
    except json.JSONDecodeError as exc:
        raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, f"invalid custom json: {exc}") from exc
    if not isinstance(payload, dict):
        raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, "custom payload must be a JSON object")
    return json.dumps(payload, ensure_ascii=False, separators=(",", ":"))
