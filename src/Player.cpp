#include <string>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Utility.h"

using namespace std;


bool operator==(const Stats& lhs, const Stats& rhs) {
	return (lhs.innings == rhs.innings) && 
		   (lhs.bat_avg == rhs.bat_avg) && 
		   (lhs.bat_sr == rhs.bat_sr) && 
		   (lhs.balls_bowled == rhs.balls_bowled) &&
		   (lhs.bowl_avg == rhs.bowl_avg) && 
		   (lhs.bowl_sr == rhs.bowl_sr) &&
		   (lhs.bowl_econ == rhs.bowl_econ) && 
		   (lhs.bat_hand == rhs.bat_hand) &&
		   (lhs.bowl_type == rhs.bowl_type);  
}


Player::Player(string c_first_name, string c_last_name, string c_initials, Stats stats) {
	first_name = c_first_name;
	initials = c_initials;
	last_name = c_last_name;

	player_stats = stats;

}



// Return initials of first and middle name, e.g. JH
string Player::get_initials() const {
	return initials;
}


// Return initials and last name, e.g. JH Smith
string Player::get_full_initials() const {
	return get_initials() + " " + last_name;
}


string Player::get_last_name() const {
	return last_name;
}


// Return full first and last name, e.g. John Smith
string Player::get_full_name() const {
	return first_name + " " + last_name;
}



Stats Player::get_stats() const {
	return player_stats;
}

// Specific getters for stats
int Player::get_innings() const {
	return player_stats.innings;
}

double Player::get_bat_avg() const {
	return player_stats.bat_avg;
}

double Player::get_bat_sr() const {
	return player_stats.bat_sr;
}

int Player::get_balls_bowled() const {
	return player_stats.balls_bowled;
}

double Player::get_bowl_avg() const {
	return player_stats.bowl_avg;
}

double Player::get_bowl_sr() const {
	return player_stats.bowl_sr;
}

double Player::get_bowl_econ() const {
	return player_stats.bowl_econ;
}

bool Player::get_bat_hand() const {
	return player_stats.bat_hand;
}

int Player::get_bowl_type() const {
	return player_stats.bowl_type;
}


void Player::inflate_bowl_avg() {
	const double INFLATION_FACTOR = 3;

	player_stats.bowl_avg *= INFLATION_FACTOR;
	player_stats.bowl_sr *= INFLATION_FACTOR;
}

bool operator==(const Player& lhs, const Player& rhs) {
	return (lhs.first_name == rhs.first_name) &&
		   (lhs.last_name == rhs.last_name) &&
		   (lhs.initials == rhs.initials) &&
		   (lhs.player_stats == rhs.player_stats);
}


/**
 * 
*/
template <typename T>
Player** sort_array(Player** list, int len, T (Player::*sort_val)() const) {
	// TODO: improve this algorithm

	Player** sorted = new Player*[len];

	// Adaption of insertion sort algorithm
	sorted[0] = list[0];
	int j;
	Player* temp;
	for (int i = 1; i < len; i++) {
		j = i;
		sorted[i] = list[i];

		while (j > 0 && (sorted[j - 1]->*sort_val)() > (sorted[j]->*sort_val)()) {
			// SWAP
			temp = sorted[j - 1];
			sorted[j - 1] = sorted[j];
			sorted[j] = temp;

			j = j - 1;
		}
	}

	return sorted;

}

// Explicit template specialisation
//template Player** sort_array<int>(Player** list, int len, int (Player::*sort_val)() const);
template Player** sort_array<double>(Player** list, int len, double (Player::*sort_val)() const);
//template Player** sort_array<std::string>(Player** list, int len, std::string (Player::*sort_val)() const);



bool operator==(const Team& lhs, const Team& rhs) {
	bool partial = (lhs.name == rhs.name) &&
	       		   (lhs.i_captain == rhs.i_captain) &&
				   (lhs.i_wk == rhs.i_wk) &&
				   (lhs.i_bowl1 == rhs.i_bowl1) &&
				   (lhs.i_bowl2 == rhs.i_bowl2);

	if (partial) {

		// Compare each player
		for (int i = 0; i < 11; i++) {
			if (lhs.players[i] != rhs.players[i]) return false;
		}
		return true;
	} else {
		return false;
	}
}





// Overload of << operator for printing team list to console
ostream& operator<<(ostream& os, const Team& team) {
	os << team.name << endl;

	// Print each player
	for (int i = 0; i < 11; i++) {
		os << i + 1 << ". " << team.players[i]->get_full_initials();
		if (i == team.i_captain) {
			os << " (c";
			if (i == team.i_wk) {
				os << ", wk";
			}
			os << ")";

		} else if (i == team.i_wk) {
			os << " (wk)";
		}


	os << endl;
	}

	return os;
	
}
