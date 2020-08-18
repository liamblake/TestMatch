/* MatchTime.h
   Class declaration for MatchTime object tracking current time in simulated match
*/

#ifndef MATCHTIME_H
#define MATCHTIME_H

#include <string>
#include <utility>
#include <iostream>
#include <gsl/gsl_rng.h>


/* Time - class storing time of day, in 24hr format.
   Overloaded addition operator += allows seconds to be added to stored time.
*/
class Time {
  // TODO: ensure input control

  private:
	  int hours;
    int mins;
   	int secs;


  public:
    Time();
    Time(int c_hours, int c_mins, int c_secs);
    Time(float f_rep);

    void set(int c_hours, int c_mins, int c_secs);
    void set(float f_rep);

    friend class MatchTime;

    // Overloaded operators
    Time& operator=(const Time& other);
    Time& operator=(const float& frep);
    Time& operator+=(unsigned int a_secs);
    friend Time& operator+(const Time &tm1, const Time &tm2);
    friend Time& operator-(const Time &tm1, const Time &tm2);
    friend bool operator==(const Time &lhs, const Time &rhs);
    friend std::ostream& operator<<(std::ostream& os, const Time& tm);

};

// Formatted print of Time struct in output stream
std::ostream& operator<<(std::ostream& os, const Time& tm);


/* MatchTime class

*/
class MatchTime {

  private:

    Time tm;
    int day;

    std::string state;
    /* Permissable match states
        "Match Start"   - Time at start of session 1, day 1
        "Session 1"     - Session 1, as defined in Parameters.h
        "Drinks 1"      - Drinks break during session 1
        "Lunch"         - Lunch break, as defined in Parameters.h
        "Session 2"     - As above
        "Drinks 2"      - As above
        "Tea"           - Tea break, as defined in Parameters.h
        "Session 3"     - As above
        "Drinks 3"      - As above
        "Innings Break" - Break between team innings
        "Rain Delay"    - Currently unused
    */

    // Indicates whether current session has been extended by 30 minutes
    bool extended;

    // For random sampling from distribution
    static gsl_rng* gen;

    // Private utility functions
    bool take_lunch();
    bool take_tea();
    bool close_day();
    bool check_state_change();

  public:
    // Default constructor - start of match, day 1
    MatchTime();
    MatchTime(Time c_tm, int c_day, std::string c_state);

    // Time controls for use by simulation
    std::pair<int, std::string> delivery(bool type, int runs);
    std::pair<int, std::string> wicket();
    std::pair<int, std::string> end_over();
    std::pair<int, std::string> drinks();
    std::string force_early_break();
    std::string extend_session();
    std::string end_innings();
    // Returned strings indicate match state, used for error checking and interaction with Match object

    // Getters
    Time get_time();
    int get_day();
    std::string get_state();

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const MatchTime& mt);
};



#endif