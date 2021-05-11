from __future__ import annotations

from abc import ABC, abstractclassmethod, abstractmethod


class CppType(ABC):
    """Abstract base type outlining the required methods for a Python mirror of a class
    defined in C++."""

    @abstractmethod
    def to_cpp(self):
        pass

    @abstractclassmethod
    def from_cpp(cls) -> CppType:
        pass
