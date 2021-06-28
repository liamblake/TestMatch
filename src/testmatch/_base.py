from __future__ import annotations

import json
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


def jsonable(cls):
    def wrapper(cls):
        @classmethod
        def dump(cls, obj, file: str):
            jsoned = obj.to_dict()
            with open(file, "w") as fp:
                json.dump(jsoned, fp=fp, indent=4)

        @classmethod
        def load(cls, file: str):
            with open(file) as fp:
                jsoned = json.load(fp)
            return cls.from_dict(jsoned)

        setattr(cls, "dump", dump)
        setattr(cls, "load", load)

        return cls

    return wrapper
