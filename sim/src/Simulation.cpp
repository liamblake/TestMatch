
#include <string>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Utility.h"

/* Over class implementations */
Over::Over(int c_over_num) {
    over_num = c_over_num;    
    num_balls = 0;
    num_legal_delivs = 0;

}

void Over::add_ball(Ball* ball) {

    // Reallocate array
    balls = arr_add_item<Ball*>(balls, num_balls, ball);

    // Check if legal delivery
    if (ball->legal) {
        num_legal_delivs++;
    }

    num_balls++;

}

// Destructor
Over::~Over() {
    delete[] balls;
}



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