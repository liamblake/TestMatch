#include "testmatch/pregame.hpp"

#include "testmatch/enums.hpp"
#include "testmatch/team.hpp"

#include <stdexcept>
#include <string>

Team* TossResult::get_bat_team() {
    switch (choice) {
        case bat:
            return winner;
        case field:
            return loser;
        default:
            // Throw exception
            throw(std::invalid_argument("Undefined TossChoice value."));
    }
}

Team* TossResult::get_bowl_team() {
    switch (choice) {
        case bat:
            return loser;
        case field:
            return winner;
        default:
            // Throw exception
            throw(std::invalid_argument("Undefined TossChoice value."));
    }
}

TossResult::operator std::string() {
    std::string output = winner->name;
    output += " won the toss and elected to ";
    output += str(choice);
    return output;
}