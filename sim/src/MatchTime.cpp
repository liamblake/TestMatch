#include <string>
#include <utility>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>
#include <gsl/gsl_rng.h>

#include "MatchTime.h"
#include "rtnorm.h"

// Global parameters
#include "Parameters.h"

using namespace std;

/* 
    Time implementations 
*/
// Default constructor - default to 12:00am
Time::Time() {
    hours = 0;
    mins = 0;
    secs = 0;
}

Time::Time(unsigned int c_hours, unsigned int c_mins, unsigned int c_secs) {
    hours = c_hours;
    mins = c_mins;
    secs = c_secs;
}
    
// Construct from float representation
Time::Time(float f_rep) {
    hours = (int) f_rep;
    mins = (int) 100*(f_rep - (int) f_rep);
    secs = 0;
}

void Time::set(unsigned int c_hours, unsigned int c_mins, unsigned int c_secs) {
    hours = c_hours;
    mins = c_mins;
    secs = c_secs;
}

void Time::set(float f_rep) {
    hours = (int) f_rep;
    mins = (int) 100*(f_rep - (int) f_rep);
    secs = 0;
}

// Overloaded += operator
Time& Time::operator+=(unsigned int a_secs) {
    int a_mins = a_secs / 60;

    secs += a_secs % 60;
    mins += a_mins % 60;
    hours += a_mins / 60;

    hours = hours % 24;

    return *this;

}

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


/* 
    MatchTime implementations 
*/
// Default constructor - start of match, day 1
MatchTime::MatchTime() {
    tm = Time(START_TIME);
    day = 1;
    state = "Match Start";

    gsl_rng_env_setup();                                    // Read variable environnement
    gsl_rng* gen = gsl_rng_alloc (gsl_rng_default);          // Rand generator allocation
}

MatchTime::MatchTime(Time c_tm, int c_day, string c_state) {
    tm = c_tm;
    day = c_day;
    state = c_state;
    extended = false;

    gsl_rng_env_setup();                                    // Read variable environnement
    gsl_rng* gen = gsl_rng_alloc (gsl_rng_default);          // Rand generator allocation
}

// Private utility functions
bool MatchTime::take_lunch() {
    if (state != "Session 1") {
        // Cannot take lunch if not in Session 1
        return false;
    }
}

bool MatchTime::take_tea() {

}

bool MatchTime::close_day() {

}

bool MatchTime::check_state_change() {
    bool changed = false;


    return changed;
}

// Time controls for use by simulation
pair<int, string> MatchTime::delivery(bool type, int runs) {
    
    // Randomnly generate time elapsed by delivery
    pair <double, double> s;
    if (type) {
        // Spin bowler
        s = rtnorm(gen, SPIN_MINDUR, SPIN_MAXDUR, SPIN_MEANDUR + runs*RUN_DUR, DEL_STDDUR);
    } else {
        // Pace bowler
        s = rtnorm(gen, PACE_MINDUR, PACE_MAXDUR, PACE_MEANDUR + runs*RUN_DUR, DEL_STDDUR);
    }

    int elapsed = (int) ceil(get<0>(s));

    check_state_change();
    pair<int, string> output = {elapsed, state};
    return output;
    

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
