""" Defines all dataclasses which are provided to the simulation.

These mirror many of the structs defined in the core C++ library."""

from __future__ import annotations

from dataclasses import dataclass
from typing import List, Optional

from dataclasses_json import dataclass_json

from ._base import Cppable, JSONable
from ._testmatch import _PitchFactors, _Player, _Stats, _Team, _Venue
from .enums import Arm, BowlType


def input(cls, **kwargs):
    return dataclass_json(dataclass(cls, **kwargs))


@input
class Stats(Cppable, JSONable):

    innings: int
    bat_avg: Optional[float]
    bat_sr: Optional[float]

    balls_bowled: int
    bowl_avg: Optional[float]
    bowl_sr: Optional[float]
    bowl_econ: float

    bat_arm: Arm = Arm.right
    bowl_arm: Arm = Arm.right
    bowl_type: BowlType = BowlType.med

    @property
    @staticmethod
    def cpp_rep():
        return _Stats


@dataclass_json
@dataclass(frozen=True)
class Player(Cppable, JSONable):

    first_name: str
    last_name: str
    initials: str

    stats: Stats

    @property
    def full_name(self) -> str:
        return f"{self.first_name} {self.last_name}"

    @property
    def full_initials(self) -> str:
        return f"{self.initials} {self.last_name}"

    @property
    @staticmethod
    def cpp_rep():
        return _Player


@input
class Team(Cppable, JSONable):
    name: str
    players: List[Player]

    idx_captain: int
    idx_wk: int
    idx_bowl1: int
    idx_bowl2: int

    def __str__(self) -> str:
        output = f"{self.name}\n"
        for i, p in enumerate(self.players):
            output += f"{i}. {p.full_name}"
            if i == self.idx_captain:
                output += " (c)"
            if i == self.idx_wk:
                output += " (wk)"
            output += "\n"

    @property
    @staticmethod
    def cpp_rep():
        return _Team


@input
class PitchFactors(Cppable, JSONable):
    seam: float
    spin: float

    @property
    @staticmethod
    def cpp_rep():
        return _PitchFactors


@dataclass_json
@dataclass(frozen=True)
class Venue(Cppable, JSONable):
    name: str
    city: str
    country: str
    pitch: PitchFactors

    @property
    @staticmethod
    def cpp_rep():
        return _Venue
