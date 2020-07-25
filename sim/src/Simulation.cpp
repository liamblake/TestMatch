
#include <string>
#include <stdlib.h>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Utility.h"
#include "MatchTime.h"


/* Innings implementations */
int Innings::inns_no = 0;

// Constructor
Innings::Innings(Team c_team_bat, Team c_team_bowl, int c_lead, int c_day, float c_day) {

  team_bat = c_team_bat;
  team_bowl = c_team_bowl;

  lead = c_lead;
  inns_no++;

}

// Private methods used in simulation process
void Innings::simulate_delivery() {

  BatterCard* batter = batters[striker];
  BowlerCard* bowler = batters[bowl_1];


  int runs;

  if (runs % 2 == 1 && runs != 5) {
    // Rotate strike
  }


  // Add additional time, sampled from modified normal distribution
  

  // Check time of day

  // Check for declaration
  if (check_declaration()) {
    inns_open = false;
  }

}

    // Check for declaration
bool check_declaration() {
  // TODO: implement declaration checking
  return false;
}

    // Choose next bowler based off of last bowler (from end)
    Player* choose_bowler(BowlerCard last_bowler);

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_fielder();

  	
    void simulate();



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}





/*
  Match implementations
*/
Match::Match(Team* home_team, Team* away_team, bool choose_XI) {
  team1 = home_team;
  team2 = away_team;

  // Choose batting order if requested
  if (choose_XI) {
    // Do nothing as of yet
  }

  // Time object - default constructor to day 1, start time
  time = MatchTime();


  ready = false;

}

void Match::simulate_toss() {

  // Winner of toss is chosen randomly - 0.5 probability either way
  double r = ((double) rand() / (RAND_MAX)) + 1;
  toss_win = (r < 0.5);


  // TODO: Implement toss election based on pitch conditions
  toss_elect = false;

}


void Match::pregame() {
  // Toss
  simulate_toss();


  // Prepare innings
  bool team_order = toss_win;

  if (team_order) {
    inns[0] = new Innings(team1, team2, 0, &time, &pitch);
  } else {

  }

  ready = true;
}
