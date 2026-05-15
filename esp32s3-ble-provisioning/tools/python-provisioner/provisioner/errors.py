from __future__ import annotations

from dataclasses import dataclass

from .models import ErrorCode


@dataclass(slots=True)
class ProvisionError(Exception):
    code: ErrorCode
    message: str

    def to_dict(self) -> dict[str, int | str]:
        return {"code": int(self.code), "name": self.code.name, "message": self.message}
