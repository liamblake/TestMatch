#include "Player.h"
#include <string>

using namespace std;

Player::Player(string c_first_name, string c_middle_name, string c_last_name, string c_team, Stats stats) {
	first_name = c_first_name;
	middle_name = c_middle_name;
	last_name = c_last_name;

	team = c_team;

	player_stats = stats;

}


Player::Player(std::string csv_entry) {
	// Split at ','
	
}


// Return initials of first and middle name, e.g. JH
string Player::get_initials() {
	
	string init = first_name.substr(0,1) + middle_name.substr(0,1);
	return init;
}


// Return initials and last name, e.g. JH Smith
string Player::get_full_initials() {
	return get_initials() + " " + last_name;
}


string Player::get_last_name() {
	return last_name;
}


// Return full first and last name, e.g. John Henry Smith
string Player::get_full_name(bool middle) {
	if (middle) {
		return first_name + " " + middle_name + " " + last_name;
	}
	else {
		return first_name + " " + last_name;
	}
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