
#include "helpers.h"
#include "enums.h"

bool is_slow_bowler(BowlType bowl_type) {
    std::string btype_str = str(bowl_type);
    return btype_str.find('f') == std::string::npos;
}