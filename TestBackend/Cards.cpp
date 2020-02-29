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
	runs = 0;
	balls = 0;
	fours = 0;
	sixes = 0;
	out = false;

}

BatStats BatterCard::get_sim_stats() {
	BatStats output;

	output.balls = balls;
	output.runs = runs;
	output.bat_avg = player->get_stats().bat_avg;
	output.bat_hand = player->get_bat_hand();

	return(output);

}

void update_score(std::string outcome);
void dismiss(Dismissal desc);
std::string get_card(void);