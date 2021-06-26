from pytest import fixture, mark
from testmatch.cards import Dismissal


@mark.parametrize("type", [])
class TestDismissal:
    @fixture
    def dism(self, type, player1, player2):
        yield Dismissal(mode=type, bowler=player1, fielder=player2)

    def test_print(self, type, dism):

        print(dism)
