#pragma once

#include <string>
#include "Player.h"

// Stores all stats required from the batter to simulate
struct BatStats {
	int balls;
	int runs;
	double bat_avg;
	int bat_hand;		// 0: right, 1: left
};

struct BowlStats {
	int balls;
	int runs;
	int wickets;
	double bowl_avg;
	int bowl_type;		// 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10: slo, 11: slu
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


// Abstract base class for bowler and batter cards
class PlayerCard {

  protected:
	Player* player;

  public:
	// Constructor
	PlayerCard(Player* c_player);
	
	virtual void update_score(std::string outcome) = 0;
	virtual std::string get_card() = 0;

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

	BatStats get_sim_stats();
	void update_score(std::string outcome);
	void dismiss(Dismissal desc);
	std::string get_card(void);

};


//
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

	BowlStats get_sim_stats();
	void update_score(std::string outcome);
	std::string get_card(void);

};