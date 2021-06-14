from pytest import fixture
from testmatch import Player, Stats


# Fixtures
@fixture
def stats1():
    yield Stats(
        innings=65,
        bat_avg=16.46,
        bat_sr=37.44,
        balls_bowled=7734,
        bowl_avg=21.59,
        bowl_sr=47.10,
        bowl_econ=2.74,
        bat_arm="right",
        bowl_arm="right",
        bowl_type="fm",
    )


@fixture
def player1(stats1):
    yield Player(first_name="Pat", last_name="Cummins", initials="PJ", stats=stats)


@fixture
def team():
    pass
