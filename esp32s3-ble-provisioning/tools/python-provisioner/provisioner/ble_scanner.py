from __future__ import annotations

from dataclasses import dataclass

from bleak import BleakScanner


@dataclass(slots=True)
class BleDevice:
    name: str
    address: str
    rssi: int | None


async def scan_ble_devices(prefix: str = "PROV_", timeout: float = 5.0) -> list[BleDevice]:
    devices = await BleakScanner.discover(timeout=timeout)
    result: list[BleDevice] = []
    for item in devices:
        name = item.name or ""
        if name.startswith(prefix):
            result.append(BleDevice(name=name, address=item.address, rssi=item.rssi))
    return result
