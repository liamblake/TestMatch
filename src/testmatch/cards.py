from __future__ import annotations

from typing import Optional, Type

from ._base import Cppable
from ._testmatch import Arm, DismType, _BatStats, _BatterCard, _Dismissal
from .inputs import Player


class Dismissal(_Dismissal):
    def __init__(
        mode: DismType,
        bowler: Optional[Player] = None,
        fielder: Optional[Player] = None,
    ):
        super().__init__(mode, bowler.cpp, fielder.cpp)

    @property
    def bowler(self) -> Optional[Player]:
        return Player.from_cpp(self._bowler)

    @property
    def fielder(self) -> Optional[Player]:
        return Player.from_cpp(self._fielder)

    @classmethod
    def _from_parent(cls, parent: _Dismissal) -> Dismissal:
        return cls(mode=parent.mode, bowler=parent._bowler, fielder=parent._fielder)


class BatStats(Cppable):
    career_bat_avg: float
    career_strike_rate: float
    bat_arm: Arm
    runs: int
    balls: int
    fours: int
    sixes: int

    def __new__(
        cls,
        career_bat_avg: float,
        career_strike_rate: float,
        bat_arm: Arm,
        runs: int,
        balls: int,
        fours: int,
        sixes: int,
    ):
        super().__new__(
            cls, career_bat_avg, career_strike_rate, bat_arm, runs, balls, fours, sixes
        )

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

    @property
    def dismissal(self) -> Optional[Dismissal]:
        return Dismissal.from_cpp()
