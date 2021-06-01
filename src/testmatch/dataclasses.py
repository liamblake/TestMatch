""" Defines all dataclasses which are provided to the simulation.

These mirror many of the structs defined in the core C++ library."""

from __future__ import annotations

from dataclasses import dataclass
from json import JSONEncoder
from typing import List


@dataclass
class Stats:

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


@dataclass(frozen=True)
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

    class _encoder(JSONEncoder):
        def default(self, o):
            pass


@dataclass
class Team:
    name: str
    players: List[Player]

    idx_captain: int
    idx_wk: int
    idx_bowl1: int
    idx_bowl2: int


@dataclass
class PitchFactors:
    seam: float
    spin: float


@dataclass(frozen=True)
class Venue:
    name: str
    city: str
    country: str
    pitch: PitchFactors
