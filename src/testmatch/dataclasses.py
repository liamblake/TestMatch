""" Defines all dataclasses which are provided to the simulation. 

These mirror many of the structs defined in the core C++ library."""

from dataclasses import dataclass
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

    def get_full_name(self) -> str:
        pass

    def get_full_initials(self) -> str:
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
