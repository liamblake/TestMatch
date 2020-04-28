/* Cards.cpp

   Contains all class implemetations 
*/

#include "pch.h"
#include "Player.h"
#include "Cards.h"

#include <string>


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
	stats.bat_avg = c_player->get_bat_avg;
	stats.strike_rate = c_player->get_bat_sr;

	// Batting hand
	// false: right, true: left
	stats.bat_hand = c_player->get_bat_hand;

	stats.runs = 0;
	stats.balls = 0;
	stats.fours = 0;
	stats.sixes = 0;

	out = false;

}

BatStats BatterCard::get_sim_stats() {
	return stats;
}

void BatterCard::update_score(int outcome) {
	.// Needs encoder

	if (outcome == "W") {
		// Assume that dismiss has also been called with appropriate details
		
	} else if (outcome == "0") {
		// Dot ball
		stats.balls += 1;

	} else if (outcome == "1") {

	}
}


void BatterCard::dismiss(std::string d_mode, Player* d_bowler, Player* d_fielder = nullptr) {

}
std::string get_card(void);