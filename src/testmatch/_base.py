from __future__ import annotations

from typing import Type


def cppable(cpp_rep: Type):
    def wrapper(cls):
        @classmethod
        def from_cpp(cls, cpp_obj):
            pass

        @property
        def cpp(self):
            pass

        setattr(cls, "_cpp_rep", cpp_rep)
        setattr(cls, "from_cpp", from_cpp)
        setattr(cls, "cpp", cpp)

        return cls

    return wrapper
