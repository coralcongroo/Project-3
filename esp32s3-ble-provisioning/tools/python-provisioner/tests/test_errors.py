from provisioner.errors import ProvisionError
from provisioner.models import ErrorCode


def test_provision_error_to_dict() -> None:
    err = ProvisionError(ErrorCode.INVALID_POP, "bad pop")
    payload = err.to_dict()
    assert payload["code"] == 1003
    assert payload["name"] == "INVALID_POP"
