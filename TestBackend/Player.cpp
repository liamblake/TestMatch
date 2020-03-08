#include "pch.h"
#include "Player.h"
#include <string>

using namespace std;

Player::Player()
{
}


Player::~Player()
{
}

// Return initials of first and middle name, e.g. JH
string Player::get_initials() {
	first_name.at(0) + middle_name.at(0);
	return "";
}


// Return initials and last name, e.g. JH Smith
string Player::get_full_initials() {
	return get_initials() + " " + last_name;
}


string Player::get_last_name() {
	return last_name;
}


// Return full first and last name, e.g. John Henry Smith
string Player::get_full_name(bool middle = false) {
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


int Player::get_bat_hand() {
	return bat_hand;
}