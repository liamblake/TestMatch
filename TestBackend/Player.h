#pragma once
#include <string>

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
};


/* Class completely describing a player and all required pregame information to 
   simulate. 
*/
class Player
{
  private:
	std::string first_name;
	std::string middle_name;
	std::string last_name;

	std::string team;

	Stats player_stats;

	bool bat_hand;
	int bowl_type;


  public:
	Player(std::string c_first_name, std::string c_middle_name, std::string c_last_name, std::string team, Stats stats, bool left_arm, std::string bowl_type);
	~Player();

	// Getters
	std::string get_initials();
	std::string get_full_initials();
	std::string get_last_name();

	// Return full first, (middle), last name
	std::string get_full_name(bool middle = false);

	std::string get_team();

	Stats get_stats();
	
	bool get_bat_hand();
	int get_bowl_type();


};

