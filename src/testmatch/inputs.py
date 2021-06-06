""" Defines all dataclasses which are provided to the simulation.

These mirror many of the structs defined in the core C++ library."""

from __future__ import annotations

from dataclasses import dataclass
from json import JSONEncoder
from typing import List

from ._base import InputStruct
from _testmatch import _PitchFactors, _Player, _Stats, _Team, _Venue


@dataclass
class Stats(InputStruct):

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
    @staticmethod
    def cpp_rep():
        return _Stats


@dataclass(frozen=True)
class Player(InputStruct):

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

    class _encoder(JSONEncoder):
        def default(self, o):
            pass

    @property
    @staticmethod
    def cpp_rep():
        return _Player


@dataclass
class Team(InputStruct):
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


@dataclass
class PitchFactors(InputStruct):
    seam: float
    spin: float

    @property
    @staticmethod
    def cpp_rep():
        return _PitchFactors


@dataclass(frozen=True)
class Venue(InputStruct):
    name: str
    city: str
    country: str
    pitch: PitchFactors

    @property
    @staticmethod
    def cpp_rep():
        return _Venue
