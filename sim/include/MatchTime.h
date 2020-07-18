/* MatchTime.h
   Class declaration for MatchTime object tracking current time in simulated match
*/

#ifndef MATCHTIME_H
#define MATCHTIME_H

#include <string>
#include <utility>
#include <iostream>
#include <gsl/gsl_rng.h>


/* tm - structure storing time of day, in 24hr format.
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
    Time(unsigned int c_hours, unsigned int c_mins, unsigned int c_secs);
    Time(float f_rep);

    void set(unsigned int c_hours, unsigned int c_mins, unsigned int c_secs);
    void set(float f_rep);

    Time& operator+=(unsigned int a_secs);

    friend class MatchTime;
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

    bool extended;

    static gsl_rng* gen;

    // Private utility functions
    void take_lunch();
    void take_tea();
    void close_day();
    bool check_state_change();

  public:
    // Default constructor - start of match, day 1
    MatchTime();
    MatchTime(Time c_tm, int c_day, std::string c_state);

    // Time controls for use by simulation
    std::pair<int, std::string> delivery(bool type, int runs);
    std::pair<int, std::string> end_over();
    std::pair<int, std::string> drinks();
    void force_early_break();
    void extend_session();

    // Getters
    Time get_time();
    int get_day();
    std::string get_state();

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const MatchTime& mt);
};



#endif