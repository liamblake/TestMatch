/* MatchTime.h
   Class declaration for MatchTime object tracking current time in simulated match
*/

#ifndef MATCHTIME_H
#define MATCHTIME_H

#include <string>
#include <utility>
#include <iostream>


/* tm - structure storing time of day, in 24hr format.
   Overloaded addition operatoir += allows seconds to be added to stored time.
*/
struct Time {
    // TODO: convert this to a class, with input management	
	int hours;
    int mins;
   	int secs;

    // Overloaded += operator
    Time& operator+=(int a_secs) {
        int a_mins = a_secs / 60;

        secs += a_secs % 60;
        mins += a_mins % 60;
        hours += a_mins / 60;

        hours = hours % 24;

        return *this;

    }

};

// Formatted print of Time struct in output stream
std::ostream& operator<<(std::ostream& os, const Time& tm);

// Convert float representation of time to Time struct
Time to_Time(float f_rep);


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

    // Private utility functions
    void take_lunch();
    void take_tea();
    void close_day();

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