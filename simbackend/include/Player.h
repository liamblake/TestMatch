#ifndef PLAYER_H
#define PLAYER_H
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
	std::string middle_name;
	std::string last_name;

	std::string team;

	Stats player_stats;

  public:
	Player(std::string c_first_name, std::string c_middle_name, std::string c_last_name, std::string c_team, Stats stats);
	// Default destructor

	// Getters
	std::string get_initials();
	std::string get_full_initials();
	std::string get_last_name();

	// Return full first, (middle), last name
	std::string get_full_name(bool middle = false);

	std::string get_team();

	Stats get_stats();

	// Specific getters for stats
	int get_innings();
	double get_bat_avg();
	double get_bat_sr();

	int get_balls_bowled();
	double get_bowl_avg();
	double get_bowl_sr();
	double get_bowl_econ();

	bool get_bat_hand();
	int get_bowl_type();

};

#endif