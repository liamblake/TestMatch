from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Type


class CppWrap(ABC):
    """Abstract base type outlining the required methods for a Python mirror of a class
    defined in C++.

    """

    @property
    @abstractmethod
    def _cpp_rep(self) -> Type:
        """Specify the corresponding C++ representation, by returning the type."""
        pass

    def to_cpp(self):
        """ """
        # Convert all member variables to a list of keyword arguments
        attrs = vars(self)
        ptype = self._cpp_rep()
        return ptype(**attrs)

    def from_cpp(cls, obj: _cpp_rep()) -> CppWrap:
        pass

        # Get all member variables
