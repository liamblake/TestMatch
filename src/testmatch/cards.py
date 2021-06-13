from typing import NamedTuple, Type

from ._base import Cppable
from ._testmatch import _BatStats, _BatterCard
from .inputs import Player


class BatStats(Cppable, NamedTuple):
    career_bat_avg: float
    career_strike_rate: float
    bat_arm: Arm
    runs: int
    balls: int
    fours: int
    sixes: int

    @property
    @staticmethod
    def cpp_rep() -> Type:
        return _BatStats

    @property
    def strike_rate(self) -> float:
        return 100 * self.runs / self.balls


class BatterCard(_BatterCard):
    def __init__(self, plyr: Player):
        super().__init__(plyr.cpp)

    @property
    def stats(self) -> BatStats:
        return BatStats.from_cpp(self._stats)
