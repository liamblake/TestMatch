
#include <string>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <exception>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Utility.h"
#include "MatchTime.h"


/* PitchCondition implementations*/
PitchCondition::PitchCondition(MatchTime* c_time) : time(c_time) {
    // Randomly generate pitch factors
}


PitchCondition::PitchCondition(double c_pace_factor, double c_spin_factor, MatchTime* c_time) : time(c_time) {
    // Check for valid factors
    if (true) {
        pace_factor = c_pace_factor;
        spin_factor = c_spin_factor;
    }
    else {
        // raise exception
        throw std::invalid_argument("Pace factor and spin factor must sum to 1.");
    }
}


/* Innings implementations */
int Innings::inns_no = 0;

// Constructor
Innings::Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, MatchTime* c_time, PitchCondition* c_pitch) {

  team_bat = c_team_bat;
  team_bowl = c_team_bowl;

  lead = c_lead;
  wkts = 0;

  inns_no++;
  
  // Create BatterCards/BowlerCards for each player
  for (int i = 0; i < 11; i++) {
    batters[i] = new BatterCard(team_bat->players[i]);
    bowlers[i] = new BowlerCard(team_bowl->players[i]);

  }

  // Get opening batters
  BatterCard* bat1 = next_batter();
  BatterCard* bat2 = next_batter();

  // First on strike is chosen randomly
  if (((double) rand() / (RAND_MAX)) < 0.5) {
    striker = bat1;
    nonstriker = bat2;
  } else {
    striker = bat2;
    nonstriker = bat1;
  }

  // Initialise batter_status array
  batter_status[0] = batter_status[1] = 1;
  for (int i = 2; i < 11; i++) {
    batter_status[i] = 0;
  }


  // Get opening bowlers
  bowl1 = bowlers[team_bowl->i_bowl1];
  bowl2 = bowlers[team_bowl->i_bowl1];

  // Initialise bowler_status array
  for (int i = 0; i < 11; i++) {
    bowler_status[i] = false;
  }
  
}


// Generates probability distribution for each possible outcome
double* Innings::MODEL_DELIVERY(BatStats bat, BowlStats bowl, MatchStats match) {
  double* output = new double[NUM_OUTCOMES];

  // PLACEHOLDER - UNIFORM DISTRIBUTION
  double step = 1/NUM_OUTCOMES; 
  output[0] = 0;
  for (int i = 1; i < NUM_OUTCOMES; i++) {
    output[i] = output[i - 1] + step;
  }

  return output;
}

int Innings::MODEL_WICKET_TYPE(int bowltype) {
  // Unencode bowltype
  std::string btype_str = unencode_bowltype(bowltype);

  std::string DISM_MODES[8] = { "b", "c", "c&b", "lbw", "ro", "st" };
  double DISM_MODE_DIST [8];

  // Check if "f" is in bowl_type - indicates whether stumpings are possible
  if (btype_str.find('f') == std::string::npos) {
    // Spinner model
    double DISM_MODE_DIST [8] = {0.157, 0.534, 0.0359, 0.201, 0.0326, 0.0387};
  } else {
    // Seamer model
    double DISM_MODE_DIST [8] = {0.175, 0.640, 0.0141, 0.144, 0.0242};
  } 

  // Sample from distribution
  std::string dism_mode = sample_cdf<std::string>(&DISM_MODES[0], 8, &DISM_MODE_DIST[0]);
  return encode_dism(dism_mode);



}



// Private methods used in simulation process
void Innings::simulate_delivery() {

    // Pass game information to delivery model

  // Get outcome probabilities
  double* probs = MODEL_DELIVERY(striker->get_sim_stats(), bowl1->get_sim_stats(), {});

  // Simulate
  std::string outcome = sample_disc<std::string>(OUTCOMES, probs, NUM_OUTCOMES, true);
  delete[] probs;

  std::pair<int, std::string> t_output;

  if (outcome == "W") {
    // Handle wicket
    

    // Create a object for fall of wicket
    fow[wkts] = {striker->get_player(), wkts + 1, runs, overs, balls};


    // Update match time
    t_output = time->delivery(false, runs);

    // Determine next batter




  } else {


    int runs;

    if (runs % 2 == 1 && runs != 5) {
      // Rotate strike
      BatterCard* temp = striker;
      striker = nonstriker;
      nonstriker = temp;

    }

  // Update match time
    t_output = time->delivery(false, runs);

  }


  // Check match state and end this delivery cycle
  inns_state = t_output.second;
  check_state();

}

    // Check for declaration
bool Innings::check_declaration() {
  // TODO: implement declaration checking
  return false;
  // AIS: never declare, may lead to some slightly absurd innings
}


// 
void Innings::check_innings_state() {

    // Win in fourth innings chase
    if (inns_no == 4 && lead > 0) {
        inns_state = "bat_win";
    } else if (wkts == 10) {
        // Team bowled out
        // Win by innings
        if (inns_no == 3 && lead < 0) {
            inns_state = "bowl_inns_win";
        } else if (inns_no == 4) {
            
            if (lead < 0) {
                // Loss in fourth innings
                inns_state = "bowl_win";
            }
            else if (lead == 0) {
                // Tie
                inns_state = "tie";
            }
            
            
        }
        else {
            inns_state = "end_bo";
        }
        
    }

    // Declaration
    if (check_declaration()) {
        inns_state = "end_dec";
    }

    // Draw
    if (time->get_day() == 5 && inns_state == "stumps") {
        inns_state = "draw";
    }
}


void Innings::end_over() {
    // Switch ends
    BatterCard* tmp = striker;
    striker = nonstriker;
    nonstriker = striker;

    

}

// Choose next bowler based off of last bowler (from end)
BowlerCard* Innings::choose_bowler() {
    // TODO: implement system
    // Placeholder: Bowlers keep bowling

};

// Select a fielder for an appropriate mode of dismissial
Player* Innings::select_catcher(bool run_out) {
  // TODO: spice this up
  // AIS: choose a random fielder (who isn't the bowler)
  // Uniform distribution, with bias towards wicketkeeper

  const double WK_PROB = 0.4;

  double r = ((double) rand() / (RAND_MAX));

  if (r < WK_PROB) {
    // Caught by wicketkeeper
    return team_bat->players[team_bat->i_wk];
  } else {
    // Randomly choose one of the 9 remaining fielders
    // Cast WK_PROB < r < 1 to integer 
    int index = (int) floor((r - WK_PROB) * 10 / (1 - WK_PROB));  

  }


}

  	
void Innings::simulate() {

  while (inns_state != "END") {
    simulate_delivery();
  }
}



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}


// Destructor
Innings::~Innings() {
  // Delete each dynamically allocated BatterCard and BowlerCard
  for (int i = 0; i < 11; i++) {
    delete batters[i], bowlers[i];
  }

  // Delete scorecard data

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


void Match::innings_change() {
    
}

