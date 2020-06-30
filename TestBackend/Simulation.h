#pragma once 

#include <string>

#include "Player.h"
#include "Cards.h" 

// Contains all information describing a team and playing XI
struct Team {
	std::string name;
	Player* players [11];

  // Indexes refer to players array
	int captain;
	int wicket_keeper;
	int bowl_open1;
	int bowl_open2;
};


// Describes a delivery
struct Ball {
  Player* bowler;
  Player* batter; 

  int outcome;
  bool legal;
  //std::string commentary

};

// Describes an over
class Over {
  private:
    int over_num;

    Ball** balls;
    int num_balls;
    int num_legal_delivs;

  public:
    // Constructor
    Over(int c_over_num);

    // going to need to dynamically increment array size somehow
    void add_ball(Ball* ball);

    // Destructor
    ~Over();

};


// An innings
class Innings {
  
  private:
  	bool simulated;

    Team team_bat;
  	Team team_bowl;

  	int inns_no;
  	bool inns_open;
  	int overs;
    int balls;
  	int team_score;
  	int team_lead;
  	int team_wkts;

    // Ball-by-ball detail
    Ball* 

    // Scorecards
  	BatterCard* batters [11];
  	BowlerCard* bowlers [11];


  	int striker;
  	int nonstriker;

    int bowl_1;
    int bowl_2; 

  	// Private methods used in simulation process
  	void simulate_delivery();

    // Check for declaration
  	bool check_declaration();

    // Choose next bowler based off of last bowler (from end)
    Player* choose_bowler(BowlerCard last_bowler);

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_fielder();


  public:
  	// Constructor
  	Innings(Team c_team_bat, Team c_team_bowl, int c_lead, int c_inns_no, int lead);
  	
    void simulate();

    // Getters
    BatterCard** get_batters();
    BowlerCard** get_bowlers();

};


class Match {

  private:

    // Pitch conditions
    double pitch_pace;
    double pitch_spin;
    double pitch_flat;


    Innings* inns[4];

    void simulate_toss();



  public:
    Match(Team home_team, Team away_team);

    void pregame();
    void start();


};