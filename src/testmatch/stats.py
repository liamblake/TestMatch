""" Defines all dataclasses which are provided to the simulation. 

These mirror many of the structs defined in the core C++ library."""

from dataclasses import dataclass
from typing import Type

from _testmatch import _Stats

from .base import CppWrap


@dataclass
class Stats(CppWrap):

    innings: int
    bat_avg: float
    bat_sr: float

    balls_bowled: int
    bowl_avg: float
    bowl_sr: float
    bowl_econ: float

    bat_arm: int
    bowl_arm: int
    bowl_type: int

    @property
    def _cpp_rep(cls) -> Type:
        return _Stats
