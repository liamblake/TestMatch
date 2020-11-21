#ifndef CARDS_H
#define CARDS_H

#include <string>
#include "Player.h"

// Stores all relevant data from batter for simulation
struct BatStats {
	// Career averages
	double bat_avg;
	double strike_rate;

	// Batting hand
	// false: right, true: left
	bool bat_hand;

	// Current innings
	int runs;
	int balls;
	int fours; 
	int sixes;

};

// Stores all relevant data from bowler for simulation
struct BowlStats {
	// Career averages
	double bowl_avg;
	double strike_rate;

	// Bowling type
	// 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10: slo, 11: slu
	int bowl_type;		

	// Current innings
	int balls;
	int overs;
	int over_balls;
	int maidens;
	int runs;
	int wickets;

	int spell_balls;
	double spell_overs;
	int spell_maidens;
	int spell_runs;
	int spell_wickets;

};

// Stores all information relating to the dismissal of a batter
class Dismissal {
  private:
	// Mode of dismissal:
	// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
	int mode;
	Player* bowler;
	Player* fielder;

	// if bowled or lbw, set fielder = NULL

  public:
	Dismissal(int c_mode, Player* c_bowler = nullptr, Player* c_fielder = nullptr);
	
	std::string print_dism();
	int get_mode();
	Player* get_bowler();
	Player* get_fielder();

};


// Abstract base class for bowler and batter cards.
class PlayerCard {

  protected:
	Player* player;

  public:
	// Constructor
	PlayerCard(Player* c_player);

	// Getter
	Player* get_player_ptr();
	
	// Pure virtual methods
	virtual void update_score(std::string outcome) = 0;
	virtual std::string print_card(void) = 0;

	// Default destructor

};


//
class BatterCard : public PlayerCard {
	// TODO: implement MATCHTIME

  private:
	BatStats stats;
	bool out;
	Dismissal* dism;

	int mins;

  public:
	BatterCard(Player* c_player);

	BatStats get_sim_stats(void);
	void update_score(std::string outcome);//, float mins);
	void dismiss(int d_mode, Player* d_bowler = nullptr, Player* d_fielder = nullptr);
	std::string print_card(void);

	~BatterCard();

};


// Contains all information relevant to a bowler bowling in an innings
class BowlerCard : public PlayerCard {

  private:
	BowlStats stats;
	bool active;

	// Rudimentary measure of bowler tiredness, improves with each passing over
	float fatigue;

	// Tracks number of runs in a current over to determine whether that over was a maiden
	bool is_maiden;

	void add_ball();

	

  public:
	BowlerCard(Player* c_player);

	BowlStats get_sim_stats(void);
	void update_score(std::string outcome);
	void start_new_spell();

	// Over passes (from same end) without bowler bowling - reduces fatigue
	void over_rest();

	std::string print_card(void);
	std::string print_spell(void);
};



//   // Contains all information describing a team and playing XI
// class TeamCard {
//   private:
//   	Team static_team;
// 	int next_in;



// 	// Utility functions - sort subset of player array
// 	Player** sort_batavg_subset(Player* subset, int len);
// 	Player** sort_bowlavg_subset(Player* subset, int len);

//   public:
// 	TeamCard(Team base_team);

// 	// Default copy constructor

// 	// Getters 
// 	std::string get_name();
// 	Player* captain();
// 	Player* wk();
// 	Player* bowl_open(bool pos);



// 	/* Returns a pointer to the next batter in the lineup. 

// 		If the manual argument is passed, attempts to find
// 		that player in those in the lineup that have not batted.
// 		If found, will return the pointer, otherwise returns nullptr.

// 		Arguments:
// 			manual (optional): a pointer to the player to search for.

// 		Output:
// 			Returns a Player pointer to the next batter in the team
// 			lineup. If manual is passed, will return 
// 	*/
// 	Player* next_batter(Player* manual = nullptr);

// 	/* Returns a pointer to a lower-order batter selected as 
// 	   as nightwatchman.

// 	   The chosen batter 

// 	*/
// 	Player* get_nightwatch();

// 	// Sorters - used for selecting bowlers and changing batting order
// 	Player** sort_batavg(bool use_dnb = false);
// 	Player** sort_bowlavg(bool use_dnb = false);
// 	// Default destructor


// };


// Describes a delivery
struct Ball {
  Player* bowler;
  Player* batter; 

  int outcome;
  bool legal;
  std::string commentary;

};

// Describes an over
class Over {
  private:
    int over_num;

    Ball** balls;
    int num_balls;
    int num_legal_delivs;

  public:
	// Iterators?

    // Constructor
    Over(int c_over_num);

    // going to need to dynamically increment array size somehow
    void add_ball(Ball* ball);

    // Destructor
    ~Over();

};


struct Extras {
  unsigned int byes;
  unsigned int legbyes;
  unsigned int noballs;
  unsigned int wides;

  std::string print();
};


struct FOW {

	Player* batter;
	unsigned int wkts;
	unsigned int runs;
	unsigned int overs;
	unsigned int balls;

	std::string print();

  // TODO: implement value checking for 0 <= balls < 6
};


class Milestone {
  private:
  	Player* player;
	int value;

	/* Pure virtual method - checks if passed value is 
	   allowed for given milestone type.
	*/
	virtual bool is_permitted(int value) = 0;

  protected:
	std::string desc;

  public:
	Milestone(Player* c_player, int c_value);

	// Getters
	Player* get_player();
	std::string get_desc();
	int get_value();

	virtual std::string string() = 0;


};

class BatMilestone : public Milestone {
  private:
	bool is_permitted(int value);

	int runs;
	int balls;
	int fours;
	int sixes;

  public:
	BatMilestone(Player* batter, int c_milestone, int c_runs, int c_balls, int c_fours, int c_sixes);

	std::string string();




};

class PartnershipMilestone : public BatMilestone {




};

class BowlMilestone : public Milestone {
  private:
	bool is_permitted(int value);

	int runs;
	int overs;
	int balls;
	int maidens;

  public:
	BowlMilestone(Player* bowler, int c_milestone, int c_runs, int c_overs, int c_balls, int c_maidens);

	std::string string();
};


class Partnership {
  private:
	Player* bat1;
	Player* bat2;

	unsigned int bat1_runs;
	unsigned int bat1_balls;

	unsigned int bat2_runs;
	unsigned int bat2_balls;

	bool not_out;


  public:
	  Partnership(Player* c_bat1, Player* c_bat2);

	  // Getters
	  Player* get_bat1();
	  Player* get_bat2();

	  unsigned int get_runs();
	  unsigned int get_balls();

	  // Setters
	  Milestone* add_runs(unsigned int runs, bool add_ball = true);
	  void end();

};

#endif
