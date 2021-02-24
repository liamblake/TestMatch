#include <string>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <exception>
#include <iomanip>
#include <sstream>

#include "Simulation.h"
#include "Player.h"
#include "Cards.h"
#include "Utility.h"
#include "MatchTime.h"


//~~~~~~~~~~~~~~ Parameters ~~~~~~~~~~~~~~//
double FieldingManager::C_WK_PROB = 0.5;
int Innings::NUM_OUTCOMES = 22;
std::vector<std::string> Innings::OUTCOMES = { "0", "1", "1b", "1lb", "1nb", "1wd",
                                              "2", "2b", "2lb", "2nb", "2wd",
                                              "3", "3b", "3lb",
                                              "4", "4b", "4lb",
                                              "5", "5nb", "5wd",
                                              "6", "W" };
int Innings::NUM_DISM_MODES = 6;
std::vector<std::string> Innings::DISM_MODES_STATIC = { "b", "c", "c&b", "lbw", "ro", "st" };

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

    // For now, send next in
    return next_ordered();



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


double BowlingManager::bowler_obj(double bowl_avg, double bowl_sr, double fatigue) {
    return 0;
}

/**
 * 
 * Logistic curve model with midpoint at x = 30 and growth rate k = 0.2
 * 
*/
double BowlingManager::take_off_prob(double fatigue) {
    return 1.0 / (1 + exp(-0.2 * (fatigue - 30)));
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
    // Rest all players who didn't bowl the over
    for (int i = 0; i < 11; i++) {
        BowlerCard* ptr = cards[i];
        if (ptr != inns_obj->bowl2) ptr->over_rest();
    }

    // Decide whether to take the current bowler off
    if (((double)rand() / (RAND_MAX)) < take_off_prob(inns_obj->bowl1->get_tiredness())) {
        // Change bowler
    }
    else return inns_obj->bowl1;

    return inns_obj->bowl1;

}


//~~~~~~~~~~~~~~ FieldingManager implementations ~~~~~~~~~~~~~~//
FieldingManager::FieldingManager(int c_wk_idx) : wk_idx(c_wk_idx) {}

void FieldingManager::set_cards(Player* c_plys[11]) {
    for (int i = 0; i < 11; i++) players[i] = c_plys[i];
}

Player* FieldingManager::select_catcher(Player* bowler, int dism_type) {
    Player** potential;
    int n;

    std::string dism = unencode_dism(dism_type);
    // Dismissals not involving a fielder
    if (dism == "b" || dism == "lbw" || dism == "c&b") return nullptr;

    // Stumping
    if (dism == "st") return players[wk_idx];


    if (dism == "ro") {
        potential = new Player* [11];
        n = 11;
    }
    else {
        potential = new Player* [10];
        n = 10;
    }

    // Don't need to do this every time
    double* cdf = new double[n];
    cdf[0] = 0;
    int j = 0;
    for (int i = 0; i < 11; i++) {
        if ((players[i] != bowler) || dism == "ro") {
            potential[j] = players[i];
            j++;
            if (j < n) {
                if (i == wk_idx) cdf[j] = cdf[j - 1] + C_WK_PROB;
                else cdf[j] = cdf[j - 1] + (1 - C_WK_PROB) / (n - 1);
            }
        }
    }

    // Randomly sample a fielder
    Player* fielder = sample_cdf<Player*>(potential, n, cdf);
    // Need to construct CDF giving more weighting to wk

    delete[] potential;
    delete[] cdf;
    return fielder;
}



//~~~~~~~~~~~~~~ Innings implementations ~~~~~~~~~~~~~~//
int Innings::NO_INNS = 0;

// Printing variables
bool Innings::AUSTRALIAN_STYLE = false;
std::string Innings::DIVIDER = "\n--------------------------------------------------------------------\n";
std::string Innings::BUFFER = "   ";

// Constructor
Innings::Innings(Team* c_team_bat, Team* c_team_bowl, int c_lead, PitchFactors* c_pitch) : 
    overs(0), balls(0), legal_delivs(0), team_score(0),
    team_bat(c_team_bat), team_bowl(c_team_bowl), lead(c_lead), 
    wkts(0), pitch(c_pitch), man_field(c_team_bowl->i_wk), is_open(true) {

  NO_INNS++;
  inns_no = NO_INNS;
  
  // Create BatterCards/BowlerCards for each player
  for (int i = 0; i < 11; i++) {
    batters[i] = new BatterCard(team_bat->players[i]);
    bowlers[i] = new BowlerCard(team_bowl->players[i]);

  }

  // Initialise managers
  man_bat.set_cards(batters);
  man_bowl.set_cards(bowlers);
  man_field.set_cards(team_bowl->players);


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

  // Active openers
  striker->activate();
  nonstriker->activate();

  // Get opening bowlers
  bowl1 = bowlers[team_bowl->i_bowl1];
  bowl2 = bowlers[team_bowl->i_bowl2];


  // This ain't a good implementation - get your functions sorted man
  temp_outcomes = new std::string[NUM_OUTCOMES];
  for (int i = 0; i < NUM_OUTCOMES; i++) temp_outcomes[i] = OUTCOMES.at(i);


  // Set-up the first over
  first_over = last_over = new Over(1);

  // Setup FOW array
  fow = new FOW[10];
  
}


// Generates probability distribution for each possible outcome
double* Innings::MODEL_DELIVERY(BatStats bat, BowlStats bowl, MatchStats match) {
  double* output = new double[NUM_OUTCOMES];

  // PLACEHOLDER - data proportions, hard-coded model
  if (unencode_bowltype(bowl.bowl_type).find('f') == std::string::npos) {
      output[0] = 0;
      output[1] = 0.700414129;
      output[2] = 0.878619915;
      output[3] = 0.879463788;
      output[4] = 0.881999123;
      output[5] = 0.884047465;
      output[6] = 0.884303973;
      output[7] = 0.919880445;
      output[8] = 0.920519855;
      output[9] = 0.921326553;
      output[10] = 0.92133027;
      output[11] = 0.921341423;
      output[12] = 0.92863144;
      output[13] = 0.928873077;
      output[14] = 0.929029212;
      output[15] = 0.976230307;
      output[16] = 0.977791656;
      output[17] = 0.978115079;
      output[18] = 0.978234039;
      output[19] = 0.978241474;
      output[20] = 0.978267496;
      output[21] = 0.985367921;
  }
  else {
      output[0] = 0;
      output[1] = 0.72505691;
      output[2] = 0.844465522;
      output[3] = 0.845466186;
      output[4] = 0.851517595;
      output[5] = 0.859254956;
      output[6] = 0.862496443;
      output[7] = 0.899248316;
      output[8] = 0.899452243;
      output[9] = 0.900194442;
      output[10] = 0.900244238;
      output[11] = 0.900298776;
      output[12] = 0.910843688;
      output[13] = 0.910879256;
      output[14] = 0.910912454;
      output[15] = 0.978537892;
      output[16] = 0.979818363;
      output[17] = 0.98124585;
      output[18] = 0.981426065;
      output[19] = 0.981497202;
      output[20] = 0.981855259;
      output[21] = 0.983420279;
  }

  return output;
}

int Innings::MODEL_WICKET_TYPE(int bowltype) {
    // This desperately needs cleaning up

    // Unencode bowltype
    std::string btype_str = unencode_bowltype(bowltype);

    std::string* DISM_MODES = new std::string[NUM_DISM_MODES];
    double* DISM_MODE_DIST = new double [NUM_DISM_MODES];

    double DISM_MODE_SPINNER[6] = { 0, 0.157, 0.692, 0.7274, 0.9286, 0.9613};
    double DISM_MODE_SEAMER[6] = { 0, 0.175, 0.815, 0.8291, 0.9731, 1};
    
    bool is_spinner = (btype_str.find('f') == std::string::npos);

  // Check if "f" is in bowl_type - indicates whether stumpings are possible
    for (int i = 0; i < NUM_DISM_MODES; i++) {
        DISM_MODES[i] = DISM_MODES_STATIC[i];
        if (is_spinner) {
            // Spinner model
            //double DISM_MODE_DIST [8] = {0.157, 0.534, 0.0359, 0.201, 0.0326, 0.0387};
            DISM_MODE_DIST[i] = DISM_MODE_SPINNER[i];
        }
        else {
            // Seamer model
            //double DISM_MODE_DIST [8] = {0.175, 0.640, 0.0141, 0.144, 0.0242, 0};
            DISM_MODE_DIST[i] = DISM_MODE_SEAMER[i];
        }
    }


  // Sample from distribution
  std::string dism_mode = sample_cdf<std::string>(DISM_MODES, NUM_DISM_MODES, DISM_MODE_DIST);

  delete[] DISM_MODE_DIST;
  delete[] DISM_MODES;
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


  // Update cards
  striker->update_score(outcome);
  bowl1->update_score(outcome);
  bool is_legal = extras.update_score(outcome);
  new_ball->legal = is_legal;

  // Add ball to over
  last_over->add_ball(new_ball);

  if (!is_quiet) {
      // Print commentary
      std::cout << comm_ball(overs, bowl1->get_player_ptr(), striker->get_player_ptr(), outcome) << std::endl;
  }

  // Handle each outcome case
  if (outcome == "W") {
    
    wkts++;

    // Randomly choose the type of dismissal
    int dism = MODEL_WICKET_TYPE(bowl1->get_player_ptr()->get_bowl_type());

    // Pick a fielder
    Player* fielder = man_field.select_catcher(bowl1->get_player_ptr(), dism);

    striker->dismiss(dism, bowl1->get_player_ptr(), fielder);

    // Create a object for fall of wicket
    fow[wkts-1] = {striker->get_player_ptr(), (unsigned int)wkts + 1, (unsigned int)team_score, (unsigned int)overs, (unsigned int)balls};
    

    // Print dismissal
    std::cout << BUFFER + striker->print_card() << std::endl;

    // Update match time
    //t_output = time->delivery(false, runs);

    // Determine next batter
    if (wkts < 10) {
        striker = man_bat.next_in(this);
        striker->activate();
        
        if (!is_quiet) {
            std::cout << striker->get_player_ptr()->get_full_name() << +" is the new batter to the crease" << std::endl;
        }

    } // All out is checked immediately after with check_state

  } else {
    int runs = outcome.front() - '0';
    team_score += runs;
    lead += runs;

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


/* Possible return values:
 *  allout - batting team is bowled out
 *  won - batting team has succesfully chased a 4th innings target
 *  draw - reached end of match time
 *  dec - batting team has declared
 * 
 **/
std::string Innings::check_state() {

    // Check for close of innings
    // Match object distinguishes different types of win
    if ((inns_no == 4 && lead > 0)) {
        // 4th innings chase
        is_open = false;
        return "win";
    }

    if (wkts == 10) {
        // Bowled out
        is_open = false;
        return "allout";
    }


    // Check for declaration
    if (check_declaration()) {
        is_open = false; 
        return "dec";
    };

    // Check for draw

    // Check for end of day

    // Check for end of over
    if (last_over->get_num_legal_delivs() == 6) {
        end_over();
    }

    return "";

}


void Innings::end_over() {
    
    if (!is_quiet) {
        std::cout << DIVIDER << std::endl << comm_over(last_over) << std::endl << DIVIDER << std::endl;
    }
    
    overs++;

    // Switch ends
    swap_batters();
    swap_bowlers();

    // Create a new over object
    Over* new_over = new Over(overs + 1);
    last_over->set_next(new_over);
    last_over = new_over;

    // Special case - second over
    if (overs == 1) {
        if (!is_quiet) {
            std::cout <<  "Opening from the other end is " + bowl1->get_player_ptr()->get_full_name() + ".\n";
        }
    }
    else {

        // Consult the bowling manager
        BowlerCard* new_bc = man_bowl.end_over(this);

        if (!is_quiet && new_bc != bowl1) {
            std::cout << "Change of bowling, " + new_bc->get_player_ptr()->get_full_name() + " into the attack.\n";
        }
        bowl1 = new_bc;
    }
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


std::string Innings::comm_ball(int overs, Player* bowler, Player* batter, std::string outcome) {
    int balls = last_over->get_num_legal_delivs();
    if (!(last_over->get_last()->legal)){
        balls++;
    }
    
    std::string output = std::to_string(overs) + "." + std::to_string(balls) + " " +
            bowler->get_last_name() + " to " + batter->get_last_name() + ", ";

    if (outcome == "W") {
        output += "OUT!";
    }
    else {
        output += outcome;
        // TODO: improve this
    }

    return output;
}


std::string Innings::comm_over(Over* over) {
    //std::cout << over << std::endl;
    std::string output = "End of Over " + std::to_string(over->get_over_num()) + 
        BUFFER + BUFFER + BUFFER + team_bat->name + ": " + score() + DIVIDER + "\n";

    // Batter bowler details
    output += striker->print_short() + BUFFER + bowl1->print_card() + "\n";
    output += nonstriker->print_short() + BUFFER + bowl2->print_card() + "\n";

    return output;
}

std::string Innings::score() {
    if (AUSTRALIAN_STYLE) return std::to_string(wkts) + "/" + std::to_string(team_score);
    else return std::to_string(team_score) + "/" + std::to_string(wkts);
}

  	
std::string Innings::simulate(bool quiet) {

    is_quiet = quiet;

    if (is_quiet) {
        std::cout << "Simulating innings..." << std::endl;
    }
    else {
        // Pre-innings chatter
        std::cout << "Here come the teams...\n"
            << team_bowl->name + " lead by captain " + (team_bowl->players[team_bowl->i_captain])->get_full_name() << ".\n"
            << bowl1->get_player_ptr()->get_full_name() + " has the new ball in hand and is about to bowl to " + striker->get_player_ptr()->get_full_name() + ".\n"
            << nonstriker->get_player_ptr()->get_full_name() + " is at the non-strikers end.\n"
            << "Let's go!\n"
            << DIVIDER << std::endl;
    }

  std::string state;
  while (is_open) {
    // Simulate a single delivery
    simulate_delivery();

    // Check match state
    state = check_state();
  }

  if (!is_quiet) {
      // Print lead
      std::cout << team_bat->name << " ";
      if (lead > 0) std::cout << "lead by ";
      else std::cout << "trail by ";
      std::cout << std::to_string(abs(lead)) << " runs.\n";
  }

  cleanup();
  return state;
}



std::string Innings::print() {

    std::string output = "";

    // Header
    output += DIVIDER + BUFFER + team_bat->name + " " + ordinal(inns_no) + " Innings\n";
    output += DIVIDER + BUFFER + "Batter " + BUFFER + BUFFER +BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + BUFFER + "R" + BUFFER + "B" + BUFFER + "4s" + BUFFER + "6s" + BUFFER + "SR";
    output += DIVIDER;

    // Print each batter
    for (int i = 0; i < 11; i++) {
        BatterCard* ptr = batters[i];
        BatStats stats = ptr->get_sim_stats();

        // Calculate strike rate
        double sr = (float)stats.runs / stats.balls * 100;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << sr;
        std::string srs = stream.str();

        if (ptr->is_active()) {
            output += BUFFER + ptr->get_player_ptr()->get_full_initials() +
                BUFFER + ptr->print_dism() + BUFFER + std::to_string(stats.runs) + 
                BUFFER + std::to_string(stats.balls) + BUFFER + std::to_string(stats.fours) +
                BUFFER + std::to_string(stats.sixes) + BUFFER + srs + "\n";
        }
    }
    // Extras
    output += "\n" + BUFFER + "Extras" + BUFFER + "(" + extras.print() + ")" + BUFFER + std::to_string(extras.total());


    output += DIVIDER;

      
    // Total score
    int over_balls = last_over->get_num_legal_delivs();
    double rr = team_score/(overs + (float)over_balls/6.0);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << rr;
    std::string s = stream.str();
    output += BUFFER + "Total" + BUFFER + BUFFER + "(" + std::to_string(overs) + " Ov, RR " + s + ")"
        + BUFFER + BUFFER + std::to_string(team_score) + DIVIDER + "\n";

    // List Did not bat, fall of wickets


    // Bowlers
    output += BUFFER + "Bowling" + BUFFER + BUFFER + "O" + BUFFER + "M" + BUFFER + "R" + BUFFER + "W" + BUFFER + "Econ" + DIVIDER;
    for (int i = 0; i < 11; i++) {
        // Calculate and format economy
        BowlerCard* ptr = bowlers[i];
        BowlStats stats = ptr->get_sim_stats();

        // Only print if they have bowled a ball
        if (stats.balls > 0) {
            std::pair<int, int> overs = balls_to_ov(stats.balls);

            // Calculate economy
            double econ = stats.runs / (overs.first + overs.second / 6.0);
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << econ;
            std::string econs = stream.str();

            output += ptr->get_player_ptr()->get_full_initials() + BUFFER +
                std::to_string(overs.first) + "." + std::to_string(overs.second) +
                BUFFER + std::to_string(stats.maidens) + BUFFER +
                std::to_string(stats.runs) + BUFFER + std::to_string(stats.wickets) +
                BUFFER + econs + "\n";
        }

        
    }


    return output;
}



// Getters
BatterCard** Innings::get_batters() {
  return batters;
}

BowlerCard** Innings::get_bowlers() {
  return bowlers;
}

bool Innings::get_is_open() {
    return is_open;
}

int Innings::get_lead() {
    return lead;
}

int Innings::get_wkts() {
    return wkts;
}

Team* Innings::get_bat_team() {
    return team_bat;
}

Team* Innings::get_bowl_team() {
    return team_bowl;
}



// Destructor
Innings::~Innings() {
    // Delete each dynamically allocated BatterCard and BowlerCard
    for (int i = 0; i < 11; i++) {
        delete batters[i], bowlers[i];
    } 

    delete[] temp_outcomes;
    delete[] fow;

    // Delete each over iteratively
    delete_linkedlist<Over>(first_over);

}









/*
  Match implementations
*/
Match::Match(Team* home_team, Team* away_team, Venue* c_venue) : team1(home_team), team2(away_team), venue(c_venue), ready(false), inns_i(0) {

  // Time object - default constructor to day 1, start time
  //time = MatchTime();

}


void Match::simulate_toss() {

  // Winner of toss is chosen randomly - 0.5 probability either way
  toss_win = (((double) rand() / (RAND_MAX)) < 0.5);


  /* Somewhat terrible fit to the toss elect probabilities in actual data
  * Note that spin_factor = 1 - seam_factor, so we only need to consider 
  * the spin factor when calculating the probability. This is based on the 
  * intuition that in extreme spinning conditions, a team will bat first, 
  * whereas in extreme seaming conditions, a team will bowl first. 
  * 
  * Using a probability rather than a hard choice adds in that extra uncertainty
  * that appears whenever human decision is involved.
  * 
  * This model, along with the entire pitch condition set-up, will probably 
  * be eventually improved.
  **/

    // Exponential model
    double a = 0.05;
    double b = log(0.9/a);
    double bat_prob = a*exp(b*venue->pitch_factors->spin);
    toss_elect = (((double) rand() / (RAND_MAX)) < bat_prob);

    // Print toss result
    std::cout << toss_str() << std::endl;

}

void Match::change_innings() {
    
    Team* new_bat, *new_bowl;

    if (inns_i == 1 && DECIDE_FOLLOW_ON(lead)) {
        // Follow on
        new_bat = inns[inns_i]->get_bat_team();
        new_bowl = inns[inns_i]->get_bowl_team();
    }
    else {
        // Standard swap
        lead *= -1;
        new_bat = inns[inns_i]->get_bowl_team();
        new_bowl = inns[inns_i]->get_bat_team();
    }

    inns_i++; 
    inns[inns_i] = new Innings(new_bat, new_bowl, lead, venue->pitch_factors);

}


bool Match::DECIDE_FOLLOW_ON(int lead, int match_balls, int last_score) {
    if (lead > 200) return false;

    // Decision tree model
    double fo_prob;

    if (lead >= -320) {
        if (match_balls >= 1215) fo_prob = 0.2105263;
        else {

        }
    }
    else fo_prob = 0.8571428;

    return ((double)rand() / (RAND_MAX)) < fo_prob;

}


std::string Match::toss_str() {
    std::string output;

    Team* ptr;
    if (toss_win) ptr = team2;
    else ptr = team1;

    output += ptr->name + " has won the toss and elected to ";

    if (toss_elect) output += "bat.";
    else output += "bowl.";

    return output;
}

void Match::pregame() {
  // Toss
  simulate_toss();

  // Set up Innings object
  if ((toss_win && toss_elect) || (!toss_win && !toss_elect)) inns[0] = new Innings(team2, team1, 0, venue->pitch_factors);
  else inns[0] = new Innings(team1, team2, 0, venue->pitch_factors);

  ready = true;
}


void Match::start(bool quiet) {

    std::string inns_state;

    while (inns_i < 4) {
        inns_state = inns[inns_i]->simulate(quiet);
        lead = inns[inns_i]->get_lead();

        if (!quiet) {
            // Print lead
            std::cout << inns[inns_i]->get_bat_team()->name << " ";
            if (lead > 0) std::cout << "lead by ";
            else std::cout << "trail by ";
            std::cout << std::to_string(abs(lead)) << " runs.\n";
        }

        // Determine if game has been won
        if (inns_i == 2 && inns_state == "allout" && lead < 0) {
            // Win by innings
            ending = new EndInningsWin(inns[inns_i]->get_bowl_team(), -lead);
            break;

        } else if (inns_i == 3) {
            // 4th innings scenarios
            if (inns_state == "allout") {
                // Tie
                if (lead == 0) { 
                    ending = new EndTie();
                } else {
                    // Bowled out
                    ending = new EndBowlWin(inns[inns_i]->get_bowl_team(), -lead);
                }

            } else if (inns_state == "win") {
                // Win chasing
                ending = new EndChaseWin(inns[inns_i]->get_bat_team(), 10 - inns[inns_i]->get_wkts());

            } else if (inns_state == "draw") {
                // Draw
                ending = new EndDraw();
            } else {
                // Raise an exception, Innings::simulate() has returned something unknown
                std::cout << "help " << inns_state << std::endl;
            }
            break;
        } else {
            // Change innings
            change_innings();
        }
    }

}

std::string Match::print_all() {
    std::string output;
    for (int i = 0; i < 4; i++) {
        if (inns[i] != nullptr) output += inns[i]->print();
    }

    output += "\n" + ending->print() + ".\n";

    return output;
}


Match::~Match() {
    // Delete each innings
    for (int i = 0; i < 4; i++) {
        delete inns[i];
    }

    delete ending;
    
}