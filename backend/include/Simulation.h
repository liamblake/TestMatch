// -*- lsst-c++ -*-
/* Simulation.h
 *
 * 
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <utility>

#include "Player.h"
#include "Cards.h" 
#include "MatchTime.h"


// Match details required in delivery model
struct MatchStats {

};


class TeamManager {
  protected:
    PlayerCard* cards [11];

    virtual void initialise() = 0;

  public:
    TeamManager(PlayerCard* c_cards [11]);

};


class BattingManager : public TeamManager {
  private:
    void initialise();
    bool batted [11];

    // Various options for determining next batter
    PlayerCard* next_ordered();
    PlayerCard* nightwatch();
    PlayerCard* promote_hitter();

  public:
    // Constructor
    BattingManager(BatterCard* c_cards [11]);

    // Get next batter in given 
    PlayerCard* next_in(Innings* inns_obj);

};


class BowlingManager : public TeamManager {
  private:
    void initialise();

    // Various options for getting a new bowler
    BowlerCard* new_pacer(BowlerCard* ignore1, BowlerCard* ignore2);
    BowlerCard* new_spinner(BowlerCard* ignore1, BowlerCard* ignore2);
    BowlerCard* part_timer(BowlerCard* ignore1, BowlerCard* ignore2);
    BowlerCard* change_it_up(BowlerCard* ignore1, BowlerCard* ignore2);

  public:
    BowlingManager(Team c_xi);

    // Manage bowler changes at end of over
    BowlerCard* end_over(Innings* inns_obj);

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_catcher(bool run_out = false);

};


// An innings
class Innings {
  private:

    // Each team
    BattingManager* team_bat;
  	BowlingManager* team_bowl;

    // General innings info
  	static int inns_no;

  	int overs;
    int balls;
    int abs_delivs;
  	int team_score;
  	int lead;
  	int wkts;

    bool open;
    std::string inns_state;

    MatchTime* time;
    PitchCondition* pitch;

    // Ball-by-ball detail
    Over* first_over;
    Over* last_over;

    // Scorecards
  	BatterCard* batters [11];
  	BowlerCard* bowlers [11];

    // Status of batters in team
    // 0 - has not batted; 1 - at crease, not out; 2 - out
    int batter_status [11];

    // Status of bowlers in team
    // false - has not bowled; true - has bowled
    bool bowler_status [11];

    // Current batters
  	BatterCard* striker;
  	BatterCard* nonstriker;

    // Bowler of current over (bowl1) and previous over (bowl2)
    BowlerCard* bowl1;
    BowlerCard* bowl2; 

    // Extras and fall-of-wicket
    Extras extras;
    FOW* fow;

    // Simulation models
    const static int NUM_OUTCOMES = 17;
    const static std::string* OUTCOMES;
    static double* MODEL_DELIVERY(BatStats bat, BowlStats bowl, MatchStats match);
    static int MODEL_WICKET_TYPE(int bowltype);

  	// Private methods used in simulation process
    
    // Simulate a delivery and update appropriate statistics
    void simulate_delivery();
    
    // Called after each delivery, checks for changes in game state, such as end of over, end of innings, declaration, scheduled break, etc.
    void check_state();

    // Check for declaration
  	bool check_declaration();

    // Handle end of over
    void end_over();

  public:
  	// Constructor
  	Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, MatchTime* c_time, PitchCondition* c_pitch);
  	
    void simulate();

    // Getters
    BatterCard** get_batters();
    BowlerCard** get_bowlers();

    bool is_open();

    // Destructor
    ~Innings();

};


class Match {

  private:
    Team* team1;    // Home team
    Team* team2;    // Away team

    int country;
    Venue* venue;

    bool ready;
    bool toss_win;      // false = team1, true = team2
    bool toss_elect;    // false = bat, true = bowl

    MatchTime time;
    std::string match_state;

    int innings;
    Innings* inns[4];

    // Private helper functions
    void simulate_toss();
    void innings_change(bool follow_on);

  public:
    Match(Team* home_team, Team* away_team, bool choose_XI = false);

    void pregame();
    void start();

    std::string print_pregame();
};




#endif // SIMULATION_h
