#include "testmatch/pregame.hpp"

#include "testmatch/enums.hpp"
#include "testmatch/team.hpp"

#include <stdexcept>

Team* Team::get_bat_team() {
    switch (choice) {
        case bat:
            return winner;
        case bowl:
            return loser;
        default:
            // Throw exception
            throw(std::invalid_argument("Undefined TossChoice value."));
    }
}

Team* Team::get_bowl_team() {
    switch (choice) {
        case bat:
            return loser;
        case bowl:
            return winner;
        default:
            // Throw exception
            throw(std::invalid_argument("Undefined TossChoice value."));
    }
}