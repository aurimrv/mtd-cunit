"""Map Proteum/IM unit operator acronyms to mutation categories."""

from __future__ import annotations


def operator_category(operator: str) -> str:
    """
    Categories follow Proteum unit-operator families:
      C* constants, O* operators, S* statements, V* variables.
    """
    op = operator.strip()
    if op.startswith("u-"):
        key = op[2:3].upper()
    elif op.startswith("I-") or op.startswith("II-"):
        return "Integration"
    else:
        key = op[:1].upper()
    return {
        "C": "Constants",
        "O": "Operators",
        "S": "Statements",
        "V": "Variables",
    }.get(key, "Other")


CATEGORY_ORDER = ["Constants", "Operators", "Statements", "Variables", "Other", "Integration"]
