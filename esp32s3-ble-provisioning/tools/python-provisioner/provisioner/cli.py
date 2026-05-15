from __future__ import annotations

import asyncio
import json
from dataclasses import asdict

import typer

from .ble_scanner import scan_ble_devices
from .custom_data import normalize_custom_data
from .errors import ProvisionError
from .provision_client import ProvisionClient
from .qr import parse_qr_json

app = typer.Typer(help="ESP32-S3 BLE provisioning CLI")


def _print_error(err: ProvisionError) -> None:
    typer.echo(json.dumps(err.to_dict(), ensure_ascii=False))
    raise typer.Exit(code=1)


@app.command("scan")
def scan(timeout: float = typer.Option(5.0, help="BLE scan timeout in seconds / BLE 扫描时长（秒）")) -> None:
    devices = asyncio.run(scan_ble_devices(timeout=timeout))
    typer.echo(json.dumps([asdict(device) for device in devices], ensure_ascii=False, indent=2))


@app.command("parse-qr")
def parse_qr(qr: str = typer.Option(..., help="QR code JSON string / 二维码 JSON 字符串")) -> None:
    try:
        payload = parse_qr_json(qr)
    except ProvisionError as err:
        _print_error(err)
    typer.echo(json.dumps(asdict(payload), ensure_ascii=False, indent=2))


@app.command("provision")
def provision(
    name: str = typer.Option(..., help="Target device name, e.g. PROV_A1B2C3 / 目标设备名"),
    ssid: str = typer.Option(..., help="Wi-Fi SSID"),
    password: str = typer.Option("", help="Wi-Fi password / Wi-Fi 密码"),
    pop: str = typer.Option(..., help="Proof of possession / PoP"),
) -> None:
    client = ProvisionClient()
    try:
        result = asyncio.run(client.provision(name=name, ssid=ssid, password=password, pop=pop))
    except ProvisionError as err:
        _print_error(err)
    typer.echo(json.dumps(asdict(result), ensure_ascii=False, indent=2))


@app.command("status")
def status(
    name: str = typer.Option(..., help="Target device name / 目标设备名"),
    pop: str = typer.Option(..., help="Proof of possession / PoP"),
) -> None:
    client = ProvisionClient()
    try:
        result = asyncio.run(client.status(name=name, pop=pop))
    except ProvisionError as err:
        _print_error(err)
    typer.echo(json.dumps(asdict(result), ensure_ascii=False, indent=2))


@app.command("custom")
def custom(
    name: str = typer.Option(..., help="Target device name / 目标设备名"),
    pop: str = typer.Option(..., help="Proof of possession / PoP"),
    json_data: str = typer.Option(..., "--json", help="Custom endpoint JSON / 自定义 endpoint JSON"),
) -> None:
    client = ProvisionClient()
    try:
        payload = normalize_custom_data(json_data)
        result = asyncio.run(client.send_custom_data(name=name, pop=pop, payload=payload))
    except ProvisionError as err:
        _print_error(err)
    typer.echo(json.dumps(asdict(result), ensure_ascii=False, indent=2))


if __name__ == "__main__":
    app()
