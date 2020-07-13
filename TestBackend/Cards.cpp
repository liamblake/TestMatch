/* Cards.cpp

   Contains all class implemetations 
*/

#include "Player.h"
#include "Cards.h"
#include "Utility.h"

#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;


/* 
	Dimissial implementations
*/
Dismissal::Dismissal(int c_mode, Player* c_bowler, Player* c_fielder) {
	mode = c_mode;
	bowler = c_bowler;
	fielder = c_fielder;
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
	} else {
		output = "run out (" + field_name + ")";
	}

	return output;

}

int Dismissal::get_mode() {
	return mode;
}

Player* Dismissal::get_bowler() {
	return bowler;
}

Player* Dismissal::get_fielder() {
	return fielder;
}


/*
	PlayerCard implementations
*/
PlayerCard::PlayerCard(Player* c_player) {
	player = c_player;
}


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

	out = false;

}

BatStats BatterCard::get_sim_stats() {
	return stats;
}

void BatterCard::update_score(string outcome) {

	if (outcome == "W") {
		stats.balls += 1;
		out = true;
		
	} else if (outcome == "0") {
		// Dot ball
		stats.balls += 1;

	} else if (outcome == "1") {
		// 1 run
		stats.runs += 1;
		stats.balls += 1;

	} else if (outcome == "2") {
		// 1 run
		stats.runs += 2;
		stats.balls += 1;

	} else if (outcome == "3") {
		// 1 run
		stats.runs += 2;
		stats.balls += 1;

	} else if (outcome == "4") {
		// 1 run
		stats.runs += 4;
		stats.balls += 1;
		stats.fours += 1;

	} else if (outcome == "5") {
		// Overthrows - 5 fives 
		stats.runs += 5;
		stats.balls += 1;
		stats.fours += 1;

		// Assume extra runs came from boundary

	} else if (outcome == "6") {
		// 6 runs
		stats.runs += 6;
		stats.balls += 1;
		stats.sixes += 1;

	} else if (outcome.substr(1,2) == "nb") {
		int runs = outcome.at(0) - '0' - 1;
		stats.runs += runs;
		stats.balls += 1;

		if (runs == 4) {
			stats.fours += 1;
		} else if (runs == 6) {
			stats.sixes += 1;
		}

	} else if (outcome.back() == 'b') {
		// Byes or leg byes
		stats.balls += 1;

	}

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
	output += to_string(stats.runs) + " (" + to_string(stats.balls) + "b " + to_string(stats.fours) + "x4 " + to_string(stats.sixes) + "x6) SR: ";
	
	if (stats.balls == 0) {
		output += "-";
	} else {
		float sr = 100* stats.runs / stats.balls;
		stringstream ss;
		ss << fixed << setprecision(2) << sr;
		output += ss.str();
	}

	return output;
}


BatterCard::~BatterCard() {
	delete dism;
}




/*
	BatterCard implementations
*/
BowlerCard::BowlerCard(Player* c_player) : PlayerCard(c_player) {
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
}

BowlStats BowlerCard::get_sim_stats(void) {
	return stats;
}

void BowlerCard::start_new_spell() {
	stats.spell_balls = 0;
	stats.spell_overs = 0;
	stats.spell_maidens = 0;
	stats.spell_runs = 0;
	stats.spell_wickets = 0;

	active = true;

}

string BowlerCard::print_card(void) {
	string output = player->get_full_initials() + " ";

	output += to_string(stats.overs) + "." + to_string(stats.over_balls) + "-";
	output += to_string(stats.maidens) + "-";
	output += to_string(stats.runs) + "-";
	output += to_string(stats.wickets);

	return output;
}

void BowlerCard::add_over() {

	if (stats.over_balls == 5) {
		stats.overs += 1;
		stats.over_balls = 0;

		if (is_maiden) {
			stats.maidens += 1;
			is_maiden = true;
		}

	} else {
		stats.over_balls += 1;
	}
}

void BowlerCard::update_score(string outcome) {

	stats.balls += 1;

	if (outcome == "W") {
		stats.wickets += 1;
		add_over();
		
	} else if (outcome.length() == 1) {
		stats.runs += stoi(outcome);

		if (outcome != "0") {
			is_maiden = false;
		}
		
		add_over();

	} else if (outcome.substr(1,2) == "nb") {
		stats.runs += outcome.at(0) - '0' - 1;
		is_maiden = false;

	} else if (outcome.substr(1,2) == "w") {
		stats.runs += outcome.at(0) - '0';
		is_maiden = false;

	} else if (outcome.back() == 'b') {
		// Byes or leg byes
		add_over();

	} 

}
