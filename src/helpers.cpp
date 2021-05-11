
#include "testmatch/helpers.hpp"

#include "testmatch/enums.hpp"

bool is_slow_bowler(BowlType bowl_type) {
    switch (bowl_type) {
        case med:
            return true;
        case offbreak:
            return true;
        case legbreak:
            return true;
        default:
            return false;
    }
}