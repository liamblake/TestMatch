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
	std::string middle_name;
	std::string last_name;

	Stats player_stats;

	int bat_hand;
	int bowl_type;


  public:
	Player(std::string c_first_name, std::string c_middle_name, std::string c_last_name, Stats stats, bool left_arm, std::string bowl_type);
	~Player();

	std::string get_initials();
	std::string get_full_initials();
	std::string get_last_name();

	// Return full first, last name
	std::string get_full_name(bool middle = false);

	Stats get_stats();
	int get_bat_hand();
};

