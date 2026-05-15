from __future__ import annotations

from dataclasses import dataclass

from .errors import ProvisionError
from .models import ErrorCode, ProvisionState


@dataclass(slots=True)
class ProvisionResult:
    code: int
    state: str
    message: str


class ProvisionClient:
    """Thin client abstraction for ESP-IDF provisioning flow.

    TODO(Security2): add Security2 username flow and SRP negotiation.
    TODO(Android): keep endpoint names and payloads aligned with Android client.
    """

    def __init__(self, transport: str = "ble") -> None:
        self.transport = transport

    async def provision(self, *, name: str, ssid: str, password: str, pop: str) -> ProvisionResult:
        if not pop:
            raise ProvisionError(ErrorCode.INVALID_POP, "PoP is required")
        if not ssid:
            raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, "ssid is required")
        return ProvisionResult(code=int(ErrorCode.OK), state=ProvisionState.PROVISION_DONE, message=f"provision request submitted to {name}")

    async def status(self, *, name: str, pop: str) -> ProvisionResult:
        if not pop:
            raise ProvisionError(ErrorCode.INVALID_POP, "PoP is required")
        return ProvisionResult(code=int(ErrorCode.OK), state=ProvisionState.WAITING_FOR_PROVISION, message=f"status queried for {name}")

    async def send_custom_data(self, *, name: str, pop: str, payload: str) -> ProvisionResult:
        if not pop:
            raise ProvisionError(ErrorCode.INVALID_POP, "PoP is required")
        if not payload:
            raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, "payload is required")
        return ProvisionResult(code=int(ErrorCode.OK), state=ProvisionState.CLOUD_BINDING, message=f"custom endpoint payload sent to {name}")
