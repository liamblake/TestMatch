#include <string>

#include "enums.h"

std::string str(Arm arm) {
    switch (arm) {
        case left:
            return "left";
        case right:
            return "right";
    }
}

char chr(Arm arm) {
    switch (arm) {
        case left:
            return 'l';
        case right:
            return 'r';
    }
}

std::string str(BowlType bowltype) {
    switch (bowltype) {
        case med:
            return "m";
        case med_fast:
            return "mf";
        case fast_med:
            return "fm";
        case fast:
            return "f";
        case offbreak:
            return "ob";
        case legbreak:
            return "lb";
    }
}

std::string long_str(Arm arm, BowlType bowltype) {
    std::string str_arm = str(arm) + "-arm";

    std::string str_bt;
    switch (bowltype) {
        case med:
            str_bt = "medium";
        case med_fast:
            str_bt = "medium-fast";
        case fast_med:
            str_bt = "fast-medium";
        case fast:
            str_bt = "fast";
        case offbreak:
            if (arm == left)
                str_bt == "wrist spin";
            else
                str_bt == "offspin";
        case legbreak:
            if (arm == left)
                str_bt == "orthodox";
            else
                str_bt == "wrist spin";
    }
}

std::string str(DismType dismtype) {
    switch (dismtype) {
        case bowled:
            return "b";
        case lbw:
            return "lbw";
        case caught:
            return "c";
        case c_and_b:
            return "c&b";
        case run_out:
            return "ro";
        case stumped:
            return "st";
    }
}
