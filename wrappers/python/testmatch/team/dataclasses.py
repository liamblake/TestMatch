"""Defines all dataclasses needed to describe a team of players.

These classes are mirrors of those defined in testmatch\team.hpp and contain methods
to convert to the Python classes to the internal C++ interfaces defined in _testmatch.
"""
from __future__ import annotations

from dataclasses import dataclass
from typing import List, Type

from _testmatch import Arm, BowlType, _Player, _Stats, _Team

from ..core import CppType


@dataclass
class Stats(CppType):
    """ """

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

    @staticmethod
    def _cpp_rep() -> Type:
        return _Stats


@dataclass(frozen=True)
class Player(CppType):
    """ """

    first_name: str
    last_name: str
    initials: str

    player_stats: Stats

    @staticmethod
    def _cpp_rep() -> Type:
        return _Player


@dataclass(frozen=True)
class Team(CppType):
    """ """

    name: str
    players: List[Player]

    i_captain: int
    i_wk: int
    i_bowl1: int
    i_bowl2: int

    @staticmethod
    def _cpp_rep() -> Type:
        return _Team
