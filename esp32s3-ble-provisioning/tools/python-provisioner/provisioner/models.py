from __future__ import annotations

from dataclasses import dataclass
from enum import Enum, IntEnum


class ProvisionState(str, Enum):
    IDLE = "IDLE"
    WAITING_FOR_PROVISION = "WAITING_FOR_PROVISION"
    BLE_ADVERTISING = "BLE_ADVERTISING"
    BLE_CONNECTED = "BLE_CONNECTED"
    SECURITY_HANDSHAKE = "SECURITY_HANDSHAKE"
    WIFI_CONFIG_RECEIVED = "WIFI_CONFIG_RECEIVED"
    WIFI_CONNECTING = "WIFI_CONNECTING"
    WIFI_CONNECTED = "WIFI_CONNECTED"
    CLOUD_BINDING = "CLOUD_BINDING"
    PROVISION_DONE = "PROVISION_DONE"
    PROVISION_FAILED = "PROVISION_FAILED"


class ErrorCode(IntEnum):
    OK = 0
    BLE_CONNECT_FAILED = 1001
    SECURITY_FAILED = 1002
    INVALID_POP = 1003
    WIFI_AP_NOT_FOUND = 2001
    WIFI_AUTH_FAILED = 2002
    WIFI_CONNECT_TIMEOUT = 2003
    DHCP_TIMEOUT = 2004
    CUSTOM_DATA_INVALID = 3001
    TOKEN_EXPIRED = 3002
    DEVICE_ALREADY_PROVISIONED = 4001
    UNKNOWN_ERROR = 5001


@dataclass(slots=True)
class QrPayload:
    ver: str
    name: str
    transport: str
    security: int
    pop: str
    product_id: str
    device_id: str
    username: str | None = None
