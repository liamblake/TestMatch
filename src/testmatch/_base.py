from __future__ import annotations

from abc import ABC, abstractclassmethod, abstractmethod, abstractstaticmethod
from typing import Type


class InputStruct(ABC):
    """Abstract base for a dataclass which corresponds to a C++ struct and is provided as input to
    the simulation.

    These classes . They must define methods for serialising and deserialising via JSON.
    """

    # There is currently no need to convert C++ structs back to the Python equivalents.
    # @classmethod
    # def from_cpp(cls, cpp_obj) -> InputStruct:
    #     pass

    def to_cpp(self):
        # Convert each member to keyword arguments
        pass

    @property
    @abstractstaticmethod
    def cpp_rep() -> Type:
        pass

    @abstractclassmethod
    def from_jsons(cls, jsons: str) -> InputStruct:
        pass

    @abstractmethod
    def to_jsons(self) -> str:
        pass
