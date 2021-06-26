from __future__ import annotations

from abc import ABC, abstractstaticmethod
from typing import Type


class Cppable(ABC):
    """Abstract base for objects which can be converted to a bound C++ type."""

    @property
    def cpp(self):
        # Convert each member to keyword arguments
        pass

    @classmethod
    def from_cpp(cls, cpp_obj) -> Cppable:
        pass

    @property
    @abstractstaticmethod
    def cpp_rep() -> Type:
        pass
