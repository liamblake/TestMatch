from __future__ import annotations

import json
from abc import ABC, abstractstaticmethod
from typing import List, Type, Union


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
    @classmethod
    def dump(cls, obj: Union[JSONable, List[JSONable]], file: str):
        jsoned = obj.to_dict()
        with open(file, "w") as fp:
            json.dump(jsoned, fp=fp, indent=4)

    @classmethod
    def load(cls, file: str) -> JSONable:
        with open(file) as fp:
            jsoned = json.load(fp)
        return cls.from_dict(jsoned)
