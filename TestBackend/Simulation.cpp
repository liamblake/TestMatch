
#include <string>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Encoders.h"

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
  	// Private methods used in simulation process
  	void simulate_delivery();

    // Check for declaration
  	bool check_declaration();

    // Choose next bowler based off of last bowler (from end)
    Player* choose_bowler(BowlerCard last_bowler);

    // Select a fielder for an appropriate mode of dismissial
  	Player* select_fielder();


  	// Constructor
  	Innings(Team c_team_bat, Team c_team_bowl, int c_lead, int c_inns_no, int lead);
  	
    void simulate();



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}