#pragma once

#include <string>
#include "Player.h"

/*
	Structures for storing related data in one object
*/

// Stores career batting stats of a player
struct BatStats {
	// Career averages
	double strike_rate;
	double bat_avg;

	// Batting hand
	// 0: right, 1: left
	int bat_hand;

	// 
};

// Stores bowling career stats of a player
struct BowlStats {
	// Career averages
	double bowl_avg;
	double strike_rate;

	// Bowling type
	// 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10: slo, 11: slu
	int bowl_type;		
};

struct BatSimStats {
	struct BowlStats;

	int runs;
	int balls;

};


// Stores all information relating to the dismissal of a batter
struct Dismissal {
	// Mode of dismissal:
	// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
	int mode;
	Player* bowler;
	Player* fielder;

	// if bowled or lbw, set fielder = NULL

};


// Abstract base class for bowler and batter cards.
class PlayerCard {

  protected:
	Player* player;

  public:
	// Constructor
	PlayerCard(Player* c_player);
	
	// Pure virtual methods
	virtual void update_score(int outcome) = 0;
	virtual std::string get_card(void) = 0;

	// Default destructor

};


//
class BatterCard : public PlayerCard {

  private:
	  int runs;
	  int balls;
	  int fours; 
	  int sixes;
	  bool out;
	  Dismissal dism;

  public:
	BatterCard(Player* c_player);

	BatStats get_sim_stats(void);
	void update_score(int outcome);
	void dismiss(std::string d_mode, Player* d_bowler, Player* d_fielder = nullptr);
	std::string get_card(void);

};


// Contains all information relevant to a bowler bowling in an innings
class BowlerCard : public PlayerCard {

  private:
	int balls;
	int overs;
	int maidens;
	int runs;
	int wickets;
	int no_balls;
	int wides;

  public:
	BowlerCard(Player* c_player);

	BowlStats get_sim_stats(void);
	void update_score(int outcome);
	std::string get_card(void);

};