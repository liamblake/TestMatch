from dataclasses import dataclass

import pytest
from testmatch.core import CppType


class ExCppClass:
    pass


@dataclass
class ExClass(CppType):
    a: int
    b: str
    c: float

    @staticmethod
    def _cpp_type():
        return ExCppClass


class TestCppType:
    @pytest.fixture
    def class_instance():
        obj = ExClass(CppType)
        yield obj
