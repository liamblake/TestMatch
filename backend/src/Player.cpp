#include <string>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Utility.h"

using namespace std;



Player::Player(string c_first_name, string c_last_name, string c_initials, Stats stats, string c_team) {
	first_name = c_first_name;
	initials = c_initials;
	last_name = c_last_name;

	team = c_team;

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


string Player::get_team() const {
	return team;
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
