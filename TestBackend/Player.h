#pragma once
#include <string>


struct Stats {
	int innings;
	double bat_avg;
	double bat_sr;

	int balls_bowled;
	double bowl_avg;
	double bowl_sr;
	double bowl_econ;

};

class Player
{
  private:
	std::string first_name;
	std::string last_name;
	Stats player_stats;

	std::string team;
	bool bat_hand;
	int bowl_type;


  public:
	Player();
	~Player();

	std::string get_initials();
	std::string get_full_initials();

	// Return full first and last name
	std::string get_full_name();
};

