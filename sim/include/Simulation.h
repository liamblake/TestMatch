#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

#include "Player.h"
#include "Cards.h" 
#include "MatchTime.h"



class PitchCondition {
  private:
    // some numbers internally describing the pitch
    

    MatchTime* time;


  public:
    // Default constructor - random pitch
    PitchCondition(MatchTime* c_time);

    PitchCondition(float somenumbers, MatchTime* c_time);

    bool toss_choice();

    // Getters for values needed for delivery simulation model
};



// An innings
class Innings {
  private:
  	bool simulated;

    Team* team_bat;
  	Team* team_bowl;

  	static int inns_no;
  	bool inns_open;
    float time;
    int day;
  	int overs;
    int balls;
  	int team_score;
  	int team_lead;
  	int team_wkts;

    MatchTime* time;
    PitchCondition* pitch;

    // Ball-by-ball detail
    Over** bbb_overs; 

    // Scorecards
  	BatterCard* batters [11];
  	BowlerCard* bowlers [11];

  	int striker;
  	int nonstriker;

    int bowl_1;
    int bowl_2; 



  	// Private methods used in simulation process
  	void simulate_delivery();

    void end_over();

    // Check for declaration
  	bool check_declaration();

    // Choose next bowler based off of last bowler (from end)
    Player* choose_bowler(BowlerCard last_bowler);

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_fielder();


  public:
  	// Constructor
  	Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, MatchTime* c_time, PitchCondition* c_pitch);
  	
    void simulate();

    // Getters
    BatterCard** get_batters();
    BowlerCard** get_bowlers();

};


class Match {

  private:
    Team* team1;
    Team* team2;

    bool ready;
    bool toss_win;      // false = team1, true = team2
    bool toss_elect;    // false = bat, true = bowl

    // Pitch conditions
    PitchCondition pitch;

    MatchTime time;

    int innings;
    Innings** inns[4];

    // Private helper functions
    void simulate_toss();
    void innings_change(bool follow_on);

  public:
    Match(Team* home_team, Team* away_team, bool choose_XI = false);

    void pregame();
    void start();


};

#endif