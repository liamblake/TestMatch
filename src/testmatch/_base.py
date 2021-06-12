from __future__ import annotations

from abc import ABC, abstractclassmethod, abstractmethod, abstractstaticmethod
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


class JSONable(ABC):
    """Abstract base for objects which can be serialised and deserialised from
    JSON.
    """

    @abstractclassmethod
    def from_jsons(cls, jsons: str) -> JSONable:
        pass

    @abstractmethod
    def to_jsons(self) -> str:
        pass
