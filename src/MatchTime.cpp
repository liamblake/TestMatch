#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "MatchTime.h"
#include "Utility.h"

using namespace std;

/*
    MatchTime implementations
*/
// Parameters
// Session time details
float MatchTime::START_TIME = 10.30;
float MatchTime::LUNCH_START = 12.30;
int MatchTime::LUNCH_DUR = 2400; // 40 minutes
float MatchTime::TEA_START = 15.10;
int MatchTime::TEA_DUR = 1200; // 20 minutes
float MatchTime::CLOSE_PLAY = 17.30;

int MatchTime::OVERCHA_DUR = 30;
int MatchTime::DRINKS_DUR = 300; // 5 minutes
int MatchTime::INNBRE_DUR = 600; // 10 minutes

// Maximum amount of time which a session can be extended by
int MatchTime::MAXIMUM_EXTEND = 1800; // 30 minutes

// Delivery duration statistics
double MatchTime::PACE_MINDUR = 25;
double MatchTime::PACE_MAXDUR = 60;
double MatchTime::SPIN_MINDUR = 15;
double MatchTime::SPIN_MAXDUR = 40;
double MatchTime::PACE_MEANDUR = 45;
double MatchTime::SPIN_MEANDUR = 30;
// const double DEL_STDDUR = 0.5;
double MatchTime::RUN_DUR = 10;

// Default constructor - start of match, day 1
MatchTime::MatchTime() {
  time = TimeOfDay(START_TIME);
  day = 1;
  state = "Match Start";
}

// Private utility functions
bool MatchTime::take_lunch() {
  if (state != "Session 1") {
    // Cannot take lunch if not in Session 1
    return false;
  }

  // Push time to end of break
  time += LUNCH_DUR;
  state = "Lunch";
}

bool MatchTime::take_tea() {
  if (state != "Session 2") {
    // Cannot take tea if not in Session 2
    return false;
  }

  // Push time to end of break
  time += TEA_DUR;
  state = "Tea";
}

bool MatchTime::close_day() {
  if (state != "Session 3") {
    // Cannot close if not in Session 3
    return false;
  }

  // Push time to end of break
  day += 1;
  time.set(START_TIME);
  state = "Stumps";
}

void MatchTime::check_state_change() {

  // Switch through each possible match state
  if (state == "Match Start") {
    if (time > START_TIME)
  } else if (state == "Session 1") {

  } else if (state == "Drinks 1") {

  } else if (state == "Lunch") {

  } else if (state == "Session 2") {

  } else if (state == "Drinks 2") {

  } else if (state == "Tea") {

  } else if (state == "Session 3") {

  } else if (state == "Drinks 3") {

  } else if (state == "Innings Break") {

  } else if (state == "Stumps") {

  } else {
    // Raise exception - unknown match state
  }
}

// Time controls for use by simulation
pair<int, string> MatchTime::delivery(bool type, int runs) {

  // Randomnly generate time elapsed by delivery
  double s;
  if (type) {
    // Spin bowler
    s = rtexp(SPIN_MEANDUR, SPIN_MINDUR, SPIN_MAXDUR) + runs * RUN_DUR;
  } else {
    // Pace bowler
    s = rtexp(PACE_MEANDUR, PACE_MINDUR, PACE_MAXDUR) + runs * RUN_DUR;
  }

  int elapsed = (int)round(s);

  check_state_change();
  pair<int, string> output = {elapsed, state};
  return output;
}

pair<int, string> MatchTime::end_over() { return {0, state}; }

pair<int, string> MatchTime::drinks() {
  time += DRINKS_DUR;

  check_state_change();
  return {DRINKS_DUR, state};
}

string MatchTime::force_early_break() {
  check_state_change();
  return state;
}

string MatchTime::extend_session() {
  check_state_change();
  return state;
}

// Getters
VarOfTime MatchTime::get_time() { return time; }

int MatchTime::get_day() { return day; }

string MatchTime::get_state() { return state; }

// Overloaded operators
ostream& operator<<(ostream& os, const MatchTime& mt) {
  os << mt.tm << ", " << mt.state << ", Day " << mt.day;
  return os;
}

// /*
//     Time implementations
// */
// // Default constructor - default to 12:00am
// Time::Time() {
//     hours = 0;
//     mins = 0;
//     secs = 0;
// }

// Time::Time(int c_hours, int c_mins, int c_secs) {
//     hours = c_hours % 24;
//     mins = c_mins % 60;
//     secs = c_secs % 60;
// }

// // Construct from float representation
// Time::Time(float f_rep) {
//     hours = (int) f_rep;
//     mins = (int) 100*(f_rep - (int) f_rep);
//     secs = 0;
// }

// void Time::set(int c_hours, int c_mins, int c_secs) {
//     hours = c_hours % 24;
//     mins = c_mins % 60;
//     secs = c_secs % 60;
// }

// void Time::set(float f_rep) {
//     hours = (int) f_rep;
//     mins = (int) 100*(f_rep - (int) f_rep);
//     secs = 0;
// }

// // Overloaded operators
// Time& Time::operator=(const Time& other) {
//     if (this != &other) {
//         hours = other.hours;
//         mins = other.mins;
//         secs = other.secs;
//     }

//     return *this;
// }

// Time& Time::operator=(const float& other) {
//     set(other);
//     return *this;
// }

// Time& Time::operator+=(unsigned int a_secs) {
//     int a_mins = a_secs / 60;

//     secs += a_secs % 60;
//     mins += a_mins % 60;
//     hours += a_mins / 60;

//     hours = hours % 24;

//     return *this;

// }

// Time& operator+(const Time &tm1, const Time &tm2) {
//     Time output(tm1.hours + tm2.hours, tm1.mins + tm2.mins, tm1.secs +
//     tm2.secs); return output;
// }

// Time& operator-(const Time &tm1, const Time &tm2) {
//     Time output(tm1.hours - tm2.hours, tm1.mins - tm2.mins, tm1.secs -
//     tm2.secs); return output;
// }

// bool operator==(const Time &lhs, const Time &rhs) {
//     return ((lhs.hours == rhs.hours) && (lhs.mins == rhs.mins) && (lhs.secs
//     == rhs.secs));
// }

// // Formatted print of Time struct in output stream
// std::ostream& operator<<(ostream& os, const Time& tm) {
//     bool am = (tm.hours < 12);
//     if (am || tm.hours == 12) {
//         os << setw(2) << setfill('0') << tm.hours << ":";
//     } else {
//         os << setw(2) << setfill('0') << tm.hours - 12 << ":";
//     }
//     os << setw(2) << setfill('0') << tm.mins << ":";
//     os << setw(2) << setfill('0') << tm.secs << " ";

//     if (am) {
//         os << "am";
//     } else {
//         os << "pm";
//     }

//     return os;
// }