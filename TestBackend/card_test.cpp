#include <iostream>
#include <string>

#include "Player.h"
#include "Cards.h"

using namespace std;

int main(void) {
    // Create a player
    Stats stats;
    Player* p = new Player("Anonymous", "", "Batter", "Australia", stats);

    delete p;
}

