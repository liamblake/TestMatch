#pragma once 

#include <string>

#include "Player.h"
#include "Cards.h"

// Contains all information describing a team and playing XI
struct Team {
	std::string name;
	Player*[11] players;

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
  //std::string commentary

};

// Describes an over
class Over {
  private:
    int over_num;

    Ball** balls;
    int num_balls;

  public:
    // Constructor
    Over(int over_num);

    // going to need to dynamically increment array size somehow
    void add_ball(int outcome);

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

  	BatterCard*[11] batters;
  	BowlerCard*[11] bowlers;

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
    BatterCard* get_batters();
    BowlerCard* get_bowlers();




};

