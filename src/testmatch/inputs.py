""" Defines all dataclasses which are provided to the simulation.

These mirror many of the structs defined in the core C++ library."""

from __future__ import annotations

from dataclasses import dataclass
from typing import List, Optional, Type

from dataclasses_json import dataclass_json

from ._base import cppable, jsonable
from ._testmatch import _PitchFactors, _Player, _Stats, _Team, _Venue
from .enums import Arm, BowlType


def inputdata(cpp_rep: Type, frozen: bool = False):
    def wrapper(cls):
        return jsonable(
            cppable(dataclass_json(dataclass(cls, frozen=frozen)), cpp_rep=cpp_rep)
        )

    return wrapper


@inputdata(cpp_rep=_Stats)
class Stats:

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


@inputdata(cpp_rep=_Player, frozen=True)
class Player:

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


@inputdata(cpp_rep=_Team)
class Team:
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
        return output


@inputdata(cpp_rep=_PitchFactors)
class PitchFactors:
    seam: float
    spin: float


@inputdata(cpp_rep=_Venue, frozen=True)
class Venue:
    name: str
    city: str
    country: str
    pitch: PitchFactors
