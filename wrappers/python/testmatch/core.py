from __future__ import annotations

from abc import ABC, abstractstaticmethod
from typing import Type


class CppType(ABC):
    """Abstract base type outlining the required methods for a Python mirror of a class
    defined in C++."""

    @abstractstaticmethod
    def _cpp_rep() -> Type:
        """Specify the corresponding C++ representation, by returning the type."""
        pass

    def to_cpp(self) -> _cpp_rep:
        """ """
        # Convert all member variables to a list of keyword arguments
        attrs = vars(self)
        ptype = self._cpp_rep()
        return ptype(**attrs)

    def from_cpp(cls, obj: _cpp_rep()) -> CppType:
        pass

        # Get all member variables
