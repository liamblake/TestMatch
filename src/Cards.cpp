/* Cards.cpp

   Contains all class implemetations
*/

#include "Cards.h"
#include "Player.h"
#include "Utility.h"

#include <cmath>
#include <exception>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

using namespace std;

/*
    Dimissial implementations
*/
Dismissal::Dismissal(int c_mode, Player* c_bowler, Player* c_fielder) {
    // Ensure dismissial mode is valid
    if (unencode_dism(c_mode) == "-") {
        throw invalid_argument(
            "c_mode must correspond to a valid dismissial. See encode_dism in "
            "Utility.h for a list of valid encodings.");
    }

    mode = c_mode;
    bowler = nullptr;
    fielder = nullptr;

    if (c_mode != encode_dism("ro")) {
        bowler = c_bowler;
    }

    if (c_mode == encode_dism("c") || c_mode == encode_dism("ro") ||
        c_mode == encode_dism("st")) {
        fielder = c_fielder;
    }
}

string Dismissal::print_dism() {
    // TODO: include options for different print formats
    string output, bowl_name, field_name;

    if (bowler != nullptr) {
        bowl_name = bowler->get_last_name();
    }
    if (fielder != nullptr) {
        field_name = fielder->get_last_name();
    }

    // Unencode mode of dismissal
    string str_mode = unencode_dism(mode);

    if (str_mode == "b" || str_mode == "lbw") {
        output = str_mode + " " + bowl_name;
    } else if (str_mode == "c" || str_mode == "st") {
        output = str_mode + " " + field_name + " b " + bowl_name;
    } else if (str_mode == "c&b") {
        output = str_mode + " " + bowl_name;
    } else {
        output = "run out (" + field_name + ")";
    }

    return output;
}

int Dismissal::get_mode() { return mode; }

Player* Dismissal::get_bowler() { return bowler; }

Player* Dismissal::get_fielder() { return fielder; }

/*
    Fatigue implementations
*/
// Distribution parameters
double Fatigue::MEAN_PACE_FATIGUE = 5;
double Fatigue::MEAN_SPIN_FATIGUE = 0.5;
double Fatigue::EXTRA_PACE_PENALTY = 1;
double Fatigue::VAR_PACE_FATIGUE = 1;
double Fatigue::VAR_SPIN_FATIGUE = 0.1;

// Uniform number generators
// std::random_device Fatigue::RD;
std::mt19937 Fatigue::GEN{RD()};

Fatigue::Fatigue(int c_bowl_type) : value(0) {

    // Set up sampling distribution
    double mean, var;
    if (is_slow_bowler(c_bowl_type)) {
        mean = MEAN_SPIN_FATIGUE;
        var = VAR_SPIN_FATIGUE;
    } else {
        mean = MEAN_PACE_FATIGUE;
        var = VAR_PACE_FATIGUE;

        // additional fatigue penalty for "f" bowlers
        if (unencode_bowltype(c_bowl_type) == "lf" ||
            unencode_bowltype(c_bowl_type) == "rf") {
            mean += EXTRA_PACE_PENALTY;
        }
    }

    dist = new std::normal_distribution<double>(mean, sqrt(var));
}

double Fatigue::get_value() { return value; }

void Fatigue::ball_bowled() { value += (*dist)(GEN); }

void Fatigue::wicket() {
    // Player gets a boost
    if (value > 0)
        value -= 3 * dist->mean();
}

void Fatigue::rest(double time) {
    // Ease fatigue
    if (value > 0)
        value -= 3 * dist->mean();
}

Fatigue::~Fatigue() { delete dist; }

/*
    PlayerCard implementations
*/
PlayerCard::PlayerCard(Player* c_player) { player = c_player; }

Player* PlayerCard::get_player_ptr() { return player; }

/*
    BatterCard implementations
*/
BatterCard::BatterCard(Player* c_player) : PlayerCard(c_player) {
    // Assume that batter has arrived at crease when object is created

    // Career averages
    stats.bat_avg = c_player->get_bat_avg();
    stats.strike_rate = c_player->get_bat_sr();

    // Batting hand
    // false: right, true: left
    stats.bat_hand = c_player->get_bat_hand();

    stats.runs = 0;
    stats.balls = 0;
    stats.fours = 0;
    stats.sixes = 0;

    active = false;
    out = false;
}

BatStats BatterCard::get_sim_stats() { return stats; }

bool BatterCard::is_active() { return active; }

void BatterCard::activate() {
    if (!active) {
        active = true;
    } else {
        // Throw exception - Batter can only be activated once
    }
}

void BatterCard::update_score(string outcome) {

    if (outcome == "W") {
        stats.balls++;
        out = true;

    } else if (outcome == "0") {
        // Dot ball
        stats.balls++;

    } else if (outcome == "1") {
        // 1 run
        stats.runs++;
        stats.balls++;

    } else if (outcome == "2") {
        // 1 run
        stats.runs += 2;
        stats.balls++;

    } else if (outcome == "3") {
        // 1 run
        stats.runs += 3;
        stats.balls++;

    } else if (outcome == "4") {
        // 1 run
        stats.runs += 4;
        stats.balls++;
        stats.fours++;

    } else if (outcome == "5") {
        // Overthrows - 5 fives
        stats.runs += 5;
        stats.balls++;
        stats.fours++;

        // Assume extra runs came from boundary

    } else if (outcome == "6") {
        // 6 runs
        stats.runs += 6;
        stats.balls++;
        stats.sixes++;

    } else if (outcome.substr(1, 2) == "nb") {
        int runs = outcome.at(0) - '0' - 1;
        stats.runs += runs;
        stats.balls++;

        if (runs == 4) {
            stats.fours++;
        } else if (runs == 6) {
            stats.sixes++;
        }

    } else if (outcome.back() == 'b') {
        // Byes or leg byes
        stats.balls++;
    }

    // Do nothing on wides
}

void BatterCard::dismiss(int d_mode, Player* d_bowler, Player* d_fielder) {
    // Construct Dismissal structure
    dism = new Dismissal(d_mode, d_bowler, d_fielder);
    out = true;
}

string BatterCard::print_card(void) {
    string output = player->get_full_initials() + " ";

    // Dismissal
    if (out) {
        output += dism->print_dism() + " ";
    } else {
        output += "not out ";
    }

    // Stats
    output += to_string(stats.runs) + " (" + to_string(stats.balls) + "b " +
              to_string(stats.fours) + "x4 " + to_string(stats.sixes) +
              "x6) SR: ";

    if (stats.balls == 0) {
        output += "-";
    } else {
        double sr = 100 * stats.runs / (double)stats.balls;
        stringstream ss;
        ss << fixed << setprecision(2) << sr;
        output += ss.str();
    }

    return output;
}

std::string BatterCard::print_short(void) {
    std::string output = player->get_full_initials() + " " +
                         std::to_string(stats.runs) + " (" +
                         std::to_string(stats.balls) + ")";

    return output;
}

std::string BatterCard::print_dism(void) {
    if (out) {
        return dism->print_dism();
    } else {
        return "not out";
    }
}

BatterCard::~BatterCard() {
    if (out)
        delete dism;
}

/*
    BatterCard implementations
*/
BowlerCard::BowlerCard(Player* c_player)
    : PlayerCard(c_player), tiredness(c_player->get_bowl_type()) {
    stats.bowl_avg = c_player->get_bowl_avg();
    stats.strike_rate = c_player->get_bowl_sr();
    stats.bowl_type = c_player->get_bowl_type();

    stats.balls = 0;
    stats.overs = 0;
    stats.over_balls = 0;
    stats.maidens = 0;
    stats.runs = 0;
    stats.wickets = 0;

    stats.spell_balls = 0;
    stats.spell_overs = 0;
    stats.spell_maidens = 0;
    stats.spell_runs = 0;
    stats.spell_wickets = 0;

    is_maiden = true;

    active = false;

    competency = DETERMINE_COMPETENCY(c_player);
}

int BowlerCard::DETERMINE_COMPETENCY(Player* player) {
    if (player->get_innings() == 0) {
        // Debut case - check role
        // TODO: Implement this

        return 2;
    }

    double avg_balls_per_match =
        (double)player->get_balls_bowled() / (double)player->get_innings();

    if (avg_balls_per_match > 30) {
        // Full-time if bowled more than 5 overs per innings on average
        return 0;
    } else if (avg_balls_per_match > 0) {
        // Part-time bowler
        return 1;
    } else {
        // Never bowls
        return 2;
    }
}

BowlStats BowlerCard::get_sim_stats(void) { return stats; }

void BowlerCard::start_new_spell() {
    stats.spell_balls = 0;
    stats.spell_overs = 0;
    stats.spell_maidens = 0;
    stats.spell_runs = 0;
    stats.spell_wickets = 0;

    active = true;
}

double BowlerCard::get_tiredness() { return tiredness.get_value(); }

int BowlerCard::get_competency() { return competency; }

void BowlerCard::over_rest() {
    active = false;
    tiredness.rest(0);
}

string BowlerCard::print_card(void) {
    string output = player->get_full_initials() + " ";

    output += to_string(stats.overs) + "." + to_string(stats.over_balls) + "-";
    output += to_string(stats.maidens) + "-";
    output += to_string(stats.runs) + "-";
    output += to_string(stats.wickets);

    return output;
}

string BowlerCard::print_spell(void) {
    string output = player->get_full_initials() + " ";

    output +=
        to_string(stats.spell_overs) + "." + to_string(stats.over_balls) + "-";
    output += to_string(stats.spell_maidens) + "-";
    output += to_string(stats.spell_runs) + "-";
    output += to_string(stats.spell_wickets);

    return output;
}

void BowlerCard::add_ball() {

    if (stats.over_balls == 5) {
        stats.overs++;
        stats.over_balls = 0;

        if (is_maiden) {
            stats.maidens++;
            stats.spell_maidens++;
            is_maiden = true;
        }

    } else {
        stats.over_balls++;
    }
}

void BowlerCard::update_score(string outcome) {

    stats.balls++;
    tiredness.ball_bowled();

    if (outcome == "W") {
        stats.wickets++;
        stats.spell_wickets++;
        add_ball();
        tiredness.wicket();

    } else if (outcome.length() == 1) {
        stats.runs += stoi(outcome);
        stats.spell_runs += stoi(outcome);

        if (outcome != "0") {
            is_maiden = false;
        }

        add_ball();

    } else if (outcome.substr(1, 2) == "nb") {
        stats.runs += outcome.at(0) - '0';
        stats.spell_runs += outcome.at(0) - '0';
        is_maiden = false;

    } else if (outcome.substr(1, 2) == "wd") {
        stats.runs += outcome.at(0) - '0';
        stats.spell_runs += outcome.at(0) - '0';
        is_maiden = false;

    } else if (outcome.back() == 'b') {
        // Byes or leg byes
        add_ball();
    }

    // Update fatigue
    tiredness.ball_bowled();
}

template <typename T>
PlayerCard** sort_array(PlayerCard** list, int len,
                        T (Player::*sort_val)() const) {
    // Extract player pointers from cards;
    Player** ply_unsrt = new Player*[len];
    for (int i = 0; i < len; i++)
        ply_unsrt[i] = list[i]->get_player_ptr();

    // Sort by desired statistic
    Player** ply_srt = sort_array<T>(ply_unsrt, len, sort_val);

    // Sort PlayerCard pointers by Player sorting
    PlayerCard** sorted = new PlayerCard*[len];
    for (int i = 0; i < len; i++) {
        int itt = 0;
        while (itt < len && ply_srt[i] != list[itt]->get_player_ptr())
            itt++;

        if (itt == len) {
            // Something has gone terribly wrong, raise an exception
        }

        sorted[i] = list[itt];

        /**
         * Definitely not the most efficient method, but for now we are
         * unlikely to need to sort arrays of more than 11 player pointers, so
         * the inefficiency shouldn't be an issue.
         **/
    }

    // Free temporarily allocated memory
    delete[] ply_unsrt;
    delete[] ply_srt;

    return sorted;
}

BatterCard** create_batting_cards(Team* team) {
    BatterCard** cards = new BatterCard*[11];
    for (int i = 0; i < 11; i++) {
        cards[i] = new BatterCard(team->players[i]);
    }

    return cards;
}
BowlerCard** create_bowling_cards(Team* team) {
    BowlerCard** cards = new BowlerCard*[11];
    for (int i = 0; i < 11; i++) {
        cards[i] = new BowlerCard(team->players[i]);
    }

    return cards;
}

/* Over class implementations */
Over::Over(int c_over_num) {
    over_num = c_over_num;

    num_balls = 0;
    num_legal_delivs = 0;

    first = last = nullptr;
}

/**
 *
 *
 */
void Over::add_ball(Ball* ball) {

    // Add to linked list
    if (last == nullptr) {
        first = last = ball;
    } else {
        last->next = ball;
        last = ball;
    }

    // Check if legal delivery
    if (ball->legal) {
        num_legal_delivs++;
    }

    num_balls++;
}

void Over::set_next(Over* p_next) { next = p_next; }

int Over::get_over_num() { return over_num; }

int Over::get_num_balls() { return num_balls; }

int Over::get_num_legal_delivs() { return num_legal_delivs; }

Ball* Over::get_first() { return first; }

Ball* Over::get_last() { return last; }

Over* Over::get_next() { return next; }

Over::~Over() {
    // Delete each ball iteratively
    delete_linkedlist<Ball>(first);
}

//~~~~~~~~~~~~~~ Extras implementations ~~~~~~~~~~~~~~//
Extras::Extras() : byes(0), legbyes(0), noballs(0), wides(0) {}

bool Extras::update_score(std::string outcome) {
    int runs = outcome.front() - '0';
    std::string query = outcome.substr(1, 2);

    if (outcome.length() == 1) {
        // Runs off bat, legal delivery
        return true;
    } else if (query == "lb") {
        // Legbyes, legal delivery
        legbyes += runs;
        return true;

    } else if (query == "nb") {
        // No ball, illegal delivery
        noballs += runs;
        return false;
    } else if (query == "wd") {
        // Wides, illegal delivery
        wides += runs;
        return false;
    } else {
        // Byes, legal delivery
        byes += runs;
        return true;
    }

    /**
     * There is a peculiar case which I am not sure how
     * to handle; What if legbyes or byes occur on a no ball?
     * By my current implementation, this will be recorded as
     * runs off the bat and awarded to the batter (ignoring the
     * additional no ball run). The ball-by-ball data I am using
     * to develop the delivery model does not make this distinguish,
     * so as it stands this is how it is done.
     **/
}

// Print methods
std::string Extras::print() {
    std::vector<std::string> strings;

    if (byes > 0) {
        strings.push_back("b " + to_string(byes));
    }

    if (legbyes > 0) {
        strings.push_back("lb " + to_string(legbyes));
    }

    if (noballs > 0) {
        strings.push_back("nb " + to_string(noballs));
    }

    if (wides > 0) {
        strings.push_back("w " + to_string(wides));
    }

    return join_str(strings, ", ");
}

int Extras::total() { return byes + legbyes + noballs + wides; }

std::string FOW::print() {
    std::string output = to_string(runs) + "-" + to_string(wkts) + " (" +
                         batter->get_full_name() + ", " + to_string(overs) +
                         "." + to_string(balls) + " ov)";

    return output;
}

//~~~~~~~~~~~~~~ Partnership Implementations ~~~~~~~~~~~~~~//
Partnership::Partnership(Player* c_bat1, Player* c_bat2)
    : runs(0), bat1(c_bat1), bat2(c_bat2), bat1_runs(0), bat1_balls(0),
      bat2_runs(0), bat2_balls(0), not_out(true) {}

Player* Partnership::get_bat1() { return bat1; }
Player* Partnership::get_bat2() { return bat2; }

unsigned int Partnership::get_runs() { return runs; }

unsigned int Partnership::get_balls() { return bat1_balls + bat2_balls; }

bool Partnership::get_not_out() { return not_out; }

void Partnership::add_runs(unsigned int n_runs, bool scorer, bool add_ball) {
    runs += n_runs;
    int ab, ar;
    if (add_ball) {
        ab = 1;
        ar = n_runs;
    } else {
        ab = 0;
        ar = 0;
    }
    if (scorer) {
        bat2_runs += ar;
        bat2_balls += ab;
    } else {
        bat1_runs += ar;
        bat1_balls += ab;
    }
}

void Partnership::end() { not_out = false; }

EndMatch::EndMatch(Team* c_winner, int c_margin)
    : winner(c_winner), margin(c_margin) {}

EndInningsWin::EndInningsWin(Team* c_winner, int c_runs)
    : EndMatch(c_winner, c_runs) {}

std::string EndInningsWin::print() {
    return winner->name + " won by an innings and " + std::to_string(margin) +
           " runs";
}

EndBowlWin::EndBowlWin(Team* c_winner, int c_runs)
    : EndMatch(c_winner, c_runs) {}

std::string EndBowlWin::print() {
    return winner->name + " won by " + std::to_string(margin) + " runs";
}

EndChaseWin::EndChaseWin(Team* c_winner, int c_wkts)
    : EndMatch(c_winner, c_wkts) {}

std::string EndChaseWin::print() {
    return winner->name + " won by " + std::to_string(margin) + " wickets";
}

EndDraw::EndDraw() : EndMatch(nullptr, 0) {}

std::string EndDraw::print() { return "Match Drawn"; }

EndTie::EndTie() {}

std::string EndTie::print() { return "Match Tied"; }

/* Milestone implementation */
// Contructor
Milestone::Milestone(Player* c_player, int c_value)
    : player(c_player), value(c_value), desc("") {
    if (is_permitted(c_value)) {
        value = c_value;
    }
}

// THIS WON'T WORK - NEED A BETTER SOLUTION

bool Milestone::is_permitted(int value) { return true; }

// Getters
Player* Milestone::get_player() { return player; }

int Milestone::get_value() { return value; }

std::string Milestone::get_desc() { return desc; }

//
///* BatMilestone implementations */
// BatMilestone::BatMilestone() {
//
//}