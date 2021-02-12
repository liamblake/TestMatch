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

//~~~~~~~~~~~~~~ BattingManager implementations ~~~~~~~~~~~~~~//
BattingManager::BattingManager() {

  // Mark each batter as inactive
  for (int i = 0; i < 11; i++) {
    batted[i] = false;

  }
}

void BattingManager::set_cards(BatterCard* c_cards[11]) {
    for (int i = 0; i < 11; i++) cards[i] = c_cards[i];
}


BatterCard* BattingManager::next_ordered() {
  
  // Find the first batter in the ordered XI who is yet to bat
  int itt = 0;
  while (batted[itt] && itt < 11) itt++;

  
  if (itt == 11) {
    // Throw exception if all players have batted

  } else {
      batted[itt] = true;
      return cards[itt];
  }


}

BatterCard* BattingManager::nightwatch() {
    return nullptr;
}

BatterCard* BattingManager::promote_hitter() {
    return nullptr;
}

BatterCard* BattingManager::next_in(Innings* inns_obj) {
  
    // Start of innings
    if (inns_obj->balls == 0) {
        return next_ordered();
    }



}



//~~~~~~~~~~~~~~ BowlingManager implementations ~~~~~~~~~~~~~~//
BowlingManager::BowlingManager() : n_over_calls(0) {};

void BowlingManager::set_cards(BowlerCard* c_cards[11]) {
    for (int i = 0; i < 11; i++) {
        cards[i] = c_cards[i];
        
        // Correct for "cheating" part-time bowlers - blow up bowling averages 
        Player* ply_ptr = cards[i]->get_player_ptr();
        if (ply_ptr->get_innings() > 0 && ply_ptr->get_balls_bowled() / ply_ptr->get_innings() < 1) {
            ply_ptr->inflate_bowl_avg();
        }
    }

}


BowlerCard* BowlingManager::new_pacer(BowlerCard* ignore1, BowlerCard* ignore2) {
    return nullptr;
}

BowlerCard* BowlingManager::new_spinner(BowlerCard* ignore1, BowlerCard* ignore2) {
    return nullptr;
}

BowlerCard* BowlingManager::part_timer(BowlerCard* ignore1, BowlerCard* ignore2) {
    return nullptr;
}

BowlerCard* BowlingManager::change_it_up(BowlerCard* ignore1, BowlerCard* ignore2) {
    return nullptr;
}

BowlerCard* BowlingManager::end_over(Innings* inns_obj) {
    return nullptr;
}


//~~~~~~~~~~~~~~ FieldingManager implementations ~~~~~~~~~~~~~~//
FieldingManager::FieldingManager(int c_wk_idx) : wk_idx(c_wk_idx) {}

void FieldingManager::set_cards(Player* c_plys[11]) {
    for (int i = 0; i < 11; i++) players[i] = c_plys[i];
}

Player* FieldingManager::select_catcher(Player* bowler, bool run_out) {
    return nullptr;
}



//~~~~~~~~~~~~~~ Innings implementations ~~~~~~~~~~~~~~//
int Innings::inns_no = 0;
int Innings::NUM_OUTCOMES = 22;
std::vector<std::string> Innings::OUTCOMES = {"0", "1", "1b", "1lb", "1nb", "1wd", 
                                              "2", "2b", "2lb", "2nb", "2wd",
                                              "3", "3b", "3lb",
                                              "4", "4b", "4lb",
                                              "5", "5lb", "5wd",
                                              "6", "W"};

// Constructor
Innings::Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, PitchFactors* c_pitch) : 
    overs(0), balls(0), legal_delivs(0), team_score(0),
    team_bat(c_team_bat), team_bowl(c_team_bowl), lead(c_lead), 
    wkts(0), pitch(c_pitch), man_field(c_team_bowl->i_wk) {

  inns_no++;
  
  // Create BatterCards/BowlerCards for each player
  for (int i = 0; i < 11; i++) {
    batters[i] = new BatterCard(team_bat->players[i]);
    bowlers[i] = new BowlerCard(team_bowl->players[i]);

  }

  // Initialise managers
  man_bat.set_cards(batters);
  man_bowl.set_cards(bowlers);
  man_field.set_cards(team_bat->players);


  // Get opening batters
  BatterCard* bat1 = man_bat.next_in(this);
  BatterCard* bat2 = man_bat.next_in(this);

  // First on strike is chosen randomly
  if (((double) rand() / (RAND_MAX)) < 0.5) {
    striker = bat1;
    nonstriker = bat2;
  } else {
    striker = bat2;
    nonstriker = bat1;
  }

  // Get opening bowlers
  bowl1 = bowlers[team_bowl->i_bowl1];
  bowl2 = bowlers[team_bowl->i_bowl2];


  // This ain't a good implementation - get your functions sorted man
  temp_outcomes = new std::string[NUM_OUTCOMES];
  for (int i = 0; i < NUM_OUTCOMES; i++) temp_outcomes[i] = OUTCOMES.at(i);


  // Set-up the first over
  first_over = last_over = new Over(1);

  
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
  std::string outcome = sample_cdf<std::string>(temp_outcomes, NUM_OUTCOMES, probs);
  delete[] probs;

  std::pair<int, std::string> t_output;

  // Create a Ball object
  balls++;
  Ball* new_ball = new Ball;
  *new_ball = { bowl1->get_player_ptr(), striker->get_player_ptr(), outcome, true, "" };
  last_over->add_ball(new_ball);

  // Update cards
  striker->update_score(outcome);
  bowl1->update_score(outcome);


  // Handle each outcome case
  if (outcome == "W") {
    
    wkts++;

    // Randomly choose the type of dismissal
    int dism = MODEL_WICKET_TYPE(bowl1->get_player_ptr()->get_bowl_type());

    // Pick a fielder
    Player* fielder = man_field.select_catcher(bowl1->get_player_ptr(), dism == encode_dism("ro"));

    striker->dismiss(dism, bowl1->get_player_ptr(), fielder);

    // Create a object for fall of wicket
    fow[wkts] = {striker->get_player_ptr(), (unsigned int)wkts + 1, (unsigned int)team_score, (unsigned int)overs, (unsigned int)balls};


    // Update match time
    //t_output = time->delivery(false, runs);

    // Determine next batter
    if (wkts < 10) {
        striker = man_bat.next_in(this);
        if (!is_quiet) {
            std::cout << striker->get_player_ptr()->get_full_name() << +" is the new batter to the crease" << std::endl;
        }
    } // All out is checked immediately after with check_state

  } else {
    int runs = outcome.front() - '0';
    team_score += runs;

    bool is_legal = extras.update_score(outcome);
    bool is_rotation;
    if (is_legal) {
        legal_delivs++;
        // Check for strike rotation
        is_rotation = runs % 2 == 1 && runs != 5;

    } else is_rotation = runs - 1 % 2 == 1;

    // Rotate strike if required
    if (is_rotation) swap_batters();

    // Update MatchTime



  }
    

}

    // Check for declaration
bool Innings::check_declaration() {
  // TODO: implement declaration checking
    return false;
  // AIS: never declare, may lead to some slightly absurd innings
}


// 
void Innings::check_state() {

    // Check for close of innings
    // Match object determines who has won, etc.
    if ((inns_no == 4 && lead > 0) || (wkts == 10)) {
        inns_state = "END";
        open = false;
        return;
    }


    // Check for declaration
    if (check_declaration()) {
        inns_state = "END_DEC";
        open = false; 
        return;
    };

    // Check for end of day

    // Check for draw


    // Check for end of over
    if (last_over->get_num_legal_delivs() == 6) {
        end_over();
    }

}


void Innings::end_over() {
    overs++;

    // Switch ends
    swap_batters();
    swap_bowlers();

    // Create a new over object
    Over* new_over = new Over(overs);
    last_over->set_next(new_over);
    last_over = new_over;

    // Consult the bowling manager
    bowl1 = man_bowl.end_over();
    
}



void Innings::swap_batters() {
    BatterCard* tmp = striker;
    striker = nonstriker;
    nonstriker = tmp;
}


void Innings::swap_bowlers() {
    BowlerCard* tmp = bowl1;
    bowl1 = bowl2;
    bowl2 = tmp;
}

void Innings::cleanup() {

}

  	
void Innings::simulate(bool quiet) {

  while (inns_state != "END" && inns_state != "END_DEC") {
    // Simulate a single delivery
    simulate_delivery();

    // Check match state
    check_state();
  }

  cleanup();
}



std::string Innings::print() {
    std::string DIVIDER = "---------------------------------------------\n";
    std::string BUFFER = "   ";
    std::string output = "";

    // Header
    output += DIVIDER + BUFFER + team_bat->name + " " + ordinal(inns_no) + " Innings\n";
    output += DIVIDER + BUFFER + "Batter ";

    return output;
}



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}

bool Innings::is_open() {
    return open;
}


// Destructor
Innings::~Innings() {
  // Delete each dynamically allocated BatterCard and BowlerCard
  for (int i = 0; i < 11; i++) {
    delete batters[i], bowlers[i];
  }

  delete[] temp_outcomes;

  // Delete each over, each ball

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
  //time = MatchTime();


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
    //inns[0] = new Innings(team1, team2, 0, &time, &pitch);
  } else {

  }

  ready = true;
}
