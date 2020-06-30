/* Cards.cpp

   Contains all class implemetations 
*/

#include "pch.h"
#include "Player.h"
#include "Cards.h"
#include "Encoders.h"

#include <string>
#include <iomanip>
#include <sstream>

using namespace std;


/* 
	Dimissial implementations
*/
Dismissal::Dismissal(int c_mode, Player* c_bowler = nullptr, Player* c_fielder = nullptr) {
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
		int runs = outcome.at(0) - '0';
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


void BatterCard::dismiss(int d_mode, Player* d_bowler = nullptr, Player* d_fielder = nullptr) {
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
	output += to_string(stats.runs) + "(" + to_string(stats.balls) + "b " + to_string(stats.fours) + "x4 " + to_string(stats.sixes) + "x6) SR: ";
	float sr = 100* stats.runs / stats.runs;
	stringstream ss;
	ss << fixed << setprecision(2) << sr;
	output += ss.str();

	return output;
}


BatterCard::~BatterCard() {
	delete dism;
}