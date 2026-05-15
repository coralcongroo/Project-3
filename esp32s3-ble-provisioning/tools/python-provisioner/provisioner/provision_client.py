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
        # TODO: Integrate official ESP-IDF Protocomm provisioning client.
        raise ProvisionError(
            ErrorCode.UNKNOWN_ERROR,
            f"provision flow not implemented yet for {name}; integrate official esp_prov/protocomm client",
        )

    async def status(self, *, name: str, pop: str) -> ProvisionResult:
        if not pop:
            raise ProvisionError(ErrorCode.INVALID_POP, "PoP is required")
        # TODO: Query official provisioning status endpoint when client integration is complete.
        return ProvisionResult(
            code=int(ErrorCode.UNKNOWN_ERROR),
            state=ProvisionState.WAITING_FOR_PROVISION.value,
            message=f"status query placeholder for {name}",
        )

    async def send_custom_data(self, *, name: str, pop: str, payload: str) -> ProvisionResult:
        if not pop:
            raise ProvisionError(ErrorCode.INVALID_POP, "PoP is required")
        if not payload:
            raise ProvisionError(ErrorCode.CUSTOM_DATA_INVALID, "payload is required")
        # TODO: Send payload to official custom endpoint once transport client is wired.
        return ProvisionResult(
            code=int(ErrorCode.UNKNOWN_ERROR),
            state=ProvisionState.CLOUD_BINDING.value,
            message=f"custom endpoint placeholder for {name}",
        )
