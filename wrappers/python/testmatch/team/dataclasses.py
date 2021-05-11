"""Defines all dataclasses needed to describe a team of players.

These classes are mirrors of those defined in testmatch\team.hpp and contain methods
to convert to the Python classes to the internal C++ interfaces defined in _testmatch.
"""
from __future__ import annotations

from dataclasses import dataclass

from _testmatch import Arm, BowlType, _Player, _Stats, _Team

from ..core import CppType


@dataclass
class Stats(CppType):
    # Batting statistics
    innings: int
    bat_avg: float
    bat_sr: float
    bat_arm: Arm

    # Bowling statistics
    balls_bowled: int
    bowl_avg: float
    bowl_sr: float
    bowl_econ: float
    bowl_arm: Arm
    bowl_type: BowlType

    def to_cpp(self) -> _Stats:
        pass

    @classmethod
    def from_cpp(cls, obj: _Stats) -> Stats:
        pass


@dataclass(frozen=True)
class Player(CppType):
    def to_cpp(self) -> _Player:
        pass

    def from_cpp(cls, obj: _Player) -> Player:
        pass


@dataclass
class Team(CppType):
    def to_cpp(self) -> _Team:
        pass

    @classmethod
    def from_cpp(cls, obj: _Team) -> Team:
        pass
