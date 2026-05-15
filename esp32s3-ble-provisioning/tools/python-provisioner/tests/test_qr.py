import pytest

from provisioner.errors import ProvisionError
from provisioner.qr import parse_qr_json


def test_parse_qr_json_ok() -> None:
    payload = parse_qr_json(
        '{"ver":"v1","name":"PROV_A1B2C3","transport":"ble","security":1,"pop":"123456","product_id":"esp32s3_demo","device_id":"A1B2C3"}'
    )
    assert payload.name == "PROV_A1B2C3"
    assert payload.security == 1


def test_parse_qr_json_missing_field() -> None:
    with pytest.raises(ProvisionError, match="missing fields"):
        parse_qr_json('{"ver":"v1"}')
