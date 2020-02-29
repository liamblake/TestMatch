#pragma once 

#include <string>

#include "Player.h"
#include "Cards.h"


struct Team {
	std::string name;
	Player*[11] players;
	int captain;
	int wicket_keeper;
	int bowl_open1;
	int bowl_open2;
};


class Scorecard {

};


class Innings {
  
  private:
  	Team team_bat;
  	Team team_bowl;

  	int inns_no;
  	bool inns_open;
  	int balls;
  	int team_score;
  	int team_lead;
  	int team_wkts;

  	BatterCard*[11] batters;
  	BowlerCard*[11] bowlers;

  	int striker;
  	int nonstriker; 

  	// Private methods used in simulation process
  	void simulate_delivery();
  	bool check_innings_close();
  	bool select_fielder();

  public:
  	// Constructor
  	Innings(Team c_team_bat, Team c_team_bowl, int c_inns_no, int c_lead);
  	Scorecard* simulate();


};