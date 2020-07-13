#include <string>
#include <utility>
#include <iostream>
#include <iomanip>
#include <exception>

#include "MatchTime.h"

// Global parameters
#include "Parameters.h"

using namespace std;

// Formatted print of Time struct in output stream
std::ostream& operator<<(ostream& os, const Time& tm) {
    bool am = (tm.hours < 12);
    if (am || tm.hours == 12) {
        os << setw(2) << setfill('0') << tm.hours << ":";
    } else {
        os << setw(2) << setfill('0') << tm.hours - 12 << ":";
    }
    os << setw(2) << setfill('0') << tm.mins << ":";
    os << setw(2) << setfill('0') << tm.secs << " ";

    if (am) {
        os << "am";
    } else {
        os << "pm";
    }

    return os;
}

// Convert float representation of time to Time struct
Time to_Time(float f_rep) {
    Time output = {(int) f_rep, (int) 100*(f_rep - (int) f_rep), 0};
    return output;
}


/* 
    MatchTime implementations 
*/
// Default constructor - start of match, day 1
MatchTime::MatchTime() {
    tm = to_Time(START_TIME);
    day = 1;
    state = "Match Start";
}

MatchTime::MatchTime(Time c_tm, int c_day, string c_state) {
    tm = c_tm;
    day = c_day;
    state = c_state;
    extended = false;
}

// Time controls for use by simulation
pair<int, string> MatchTime::delivery(bool type, int runs) {

}

pair<int, string> MatchTime::end_over() {

}

pair<int, string> MatchTime::drinks() {

}

void MatchTime::force_early_break() {

}

void MatchTime::extend_session() {

}

// Getters
Time MatchTime::get_time() {
    return tm;
}

int MatchTime::get_day() {
    return day;
}

string MatchTime::get_state() {
    return state;
}

// Overloaded operators
ostream& operator<<(ostream& os, const MatchTime& mt) {
    os << mt.tm << ", " << mt.state << ", Day " << mt.day;
    return os; 
}
