#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

/* 
*/
//class OverCount {
//  
//  private:
//	int overs;
//	int balls;
//
//	// Internal addition of ball
//	void add_ball(int add = 1);
//
//  public:
//	OverCount();
//	OverCount(int c_overs, int c_balls);
//
//	int as_balls();
//
//	// Copy constrecutor
//	OverCount(const OverCount& oc);
//
//	// Overloaded operators
//	OverCount& operator++();
//	OverCount& operator++(int);
//	OverCount& operator+=(const int rhs);
//	friend OverCount operator+(const OverCount& lhs, const OverCount& rhs);
//	friend OverCount operator+(const OverCount& lhs, const int rhs);
//	friend bool operator==(const OverCount& lhs, const OverCount& rhs);
//	friend bool operator!=(const OverCount& lhs, const OverCount& rhs);
//	friend bool operator<(const OverCount& lhs, const OverCount& rhs);
//	friend bool operator>(const OverCount& lhs, const OverCount& rhs);
//	friend bool operator<=(const OverCount& lhs, const OverCount& rhs);
//	friend bool operator>=(const OverCount& lhs, const OverCount& rhs);
//
//	explicit operator std::string() const;
//	explicit operator float() const;
//
//};


/* Structure containing all statistics describing a player. These are available in the /data/players
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
	// Explicit constructor
	Player(std::string c_first_name, std::string c_last_name, std::string c_initials, Stats stats, std::string c_team = "");
	
	// Default destructor

	// Getters
	std::string get_initials() const;
	std::string get_last_name() const;

	// Return full first, last name
	std::string get_full_name() const;
	std::string get_full_initials() const;

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

template <typename T>
Player** sort_array(Player** list, int len, T (Player::*sort_val)() const);


struct Team {
	std::string name;
	Player* players[11];

	// Indexes refer to players array
	int i_captain;
	int i_wk;
	int i_bowl1;
	int i_bowl2;
};



// Overload of << operator for printing team list to console
std::ostream& operator<<(std::ostream& os, const Team& team);
// Primarily used for testing


#endif