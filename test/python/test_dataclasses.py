from pytest import fixture
from testmatch import Player, Stats


@fixture
def stats():
    yield Stats()


@fixture
def player(stats):
    yield Player(first_name="Pat", last_name="Cummins", initials="PJ", stats=stats)


class TestPlayer:
    def test_names(self, player):
        """
        GIVEN: A Player object.
        WHEN: Getting a formatted name with full_name or full_initials.
        THEN: The names are formatted correctly.
        """

        assert player.full_name == "Pat Cummins"
        assert player.full_initials == "PJ Cummins"
