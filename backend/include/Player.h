#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

/* Structure containing all statistics describing a player. These are available in the DataAnalysis/data/players
   directory. */
struct Stats {
	int innings;
	double bat_avg;
	double bat_sr;

	int balls_bowled;
	double bowl_avg;
	double bowl_sr;
	double bowl_econ;

	bool bat_hand;
	int bowl_type;


};


/* Class completely describing a player and all required pregame information to 
   simulate. 
*/
class Player
{
  private:
	std::string first_name;
	std::string last_name;

	std::string initials;

	std::string team;

	Stats player_stats;

  public:
	Player(std::string c_first_name, std::string c_last_name, std::string c_initials, Stats stats, std::string c_team = "");
	Player(std::string line);
	
	// Default destructor

	// Getters
	std::string get_initials() const;
	std::string get_full_initials() const;
	std::string get_last_name() const;

	// Return full first, (middle), last name
	std::string get_full_name() const;

	std::string get_team() const;

	Stats get_stats() const;

	// Specific getters for stats
	int get_innings() const;
	double get_bat_avg() const;
	double get_bat_sr() const;

	int get_balls_bowled() const;
	double get_bowl_avg() const;
	double get_bowl_sr() const;
	double get_bowl_econ() const;

	bool get_bat_hand() const;
	int get_bowl_type() const;

};

  // Contains all information describing a team and playing XI
class Team {
  private:
  	std::string name;
	Player* players [11];
	int dnb [11];

    // Indexes refer to players array
	int i_captain;
	int i_wk;
	int i_bowl1;
	int i_bowl2;

  public:
	Team(std::string c_name, Player* c_players [11], std::string ind_line);
	Team(std::string csv);

	// Default copy constructor

	// Getters 
	std::string get_name();
	Player* captain();
	Player* wk();
	Player* bowl_open(bool pos);


	/* Returns a pointer to the next batter in the lineup. 

		If the manual argument is passed, attempts to find
		that player in those in the lineup that have not batted.
		If found, will return the pointer, otherwise returns nullptr.

		Arguments:
			manual (optional): a pointer to the player to search for.

		Output:
			Returns a Player pointer to the next batter in the team
			lineup. If manual is passed, will return 
	*/
	Player* next_batter(Player* manual = nullptr);
	Player* get_nightwatch();



	// Sorters - used for selecting bowlers and changing batting order
	Player** sort_batavg(bool use_dnb = false);
	Player** sort_bowlavg(bool use_dnb = false);
	// Default destructor


	// Overload of << operator for printing team list to console
	friend std::ostream& operator<<(std::ostream& os, const Team& team);
	// Primarily used for testing

};

#endif