#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(string c_first_name, string c_last_name, string c_initials, Stats stats, string c_team) {
	first_name = c_first_name;
	initials = c_initials;
	last_name = c_last_name;

	team = c_team;

	player_stats = stats;

}


// Return initials of first and middle name, e.g. JH
string Player::get_initials() {
	return initials;
}


// Return initials and last name, e.g. JH Smith
string Player::get_full_initials() {
	return get_initials() + " " + last_name;
}


string Player::get_last_name() {
	return last_name;
}


// Return full first and last name, e.g. John Smith
string Player::get_full_name() {
	return first_name + " " + last_name;
}


string Player::get_team() {
	return team;
}


Stats Player::get_stats() {
	return player_stats;
}

// Specific getters for stats
int Player::get_innings() {
	return player_stats.innings;
}

double Player::get_bat_avg() {
	return player_stats.bat_avg;
}

double Player::get_bat_sr() {
	return player_stats.bat_sr;
}

int Player::get_balls_bowled() {
	return player_stats.balls_bowled;
}

double Player::get_bowl_avg() {
	return player_stats.bowl_avg;
}

double Player::get_bowl_sr() {
	return player_stats.bowl_sr;
}

double Player::get_bowl_econ() {
	return player_stats.bowl_econ;
}

bool Player::get_bat_hand() {
	return player_stats.bat_hand;
}

int Player::get_bowl_type() {
	return player_stats.bowl_type;
}


// Overload of << operator for printing team list to console
ostream& operator<<(ostream& os, const Team& team) {
	os << team.name << endl;

	// Print each player
	for (int i = 0; i < 11; i++) {
		os << i + 1 << ". " << team.players[i]->get_full_initials();
		if (i == team.captain) {
			os << " (c";
			if (i == team.wicket_keeper) {
				os << ", wk";
			}
			os << ")";

		} else if (i == team.wicket_keeper) {
			os << " (wk)";
		}


	os << endl;
	}

	return os;
	
}