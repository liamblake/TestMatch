// -*- lsst-c++ -*-
/* Player.h
 *
 * Interface for basic player storage types. 
 * 
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>


/**
 * @brief Storage for all career statistics of an individual player
 * 
 * Self-explanatory, contains basic data types storing each relevant statistic.
 * See each declaration for a more detailed explanation.
 * 
*/
struct Stats {
	// Batting statistics
	int innings;		// Number of innings batted over career
	double bat_avg;		// Batting average (average runs per dismissal)
	double bat_sr;		// Batting strike rate (average runs per 100 balls faced)

	// Bowling statistics
	int balls_bowled;	// Number of balls bowled over career
	double bowl_avg;	// Bowling average (average runs conceded per wicket)
	double bowl_sr;		// Bowling strike rate (average balls bowled per wicket)
	double bowl_econ;	// Bowling economy (average runs conceded per 6 balls bowled)

	// General descriptors
	bool bat_hand;		// Batting hand (false = right, true = left)
	int bowl_type;		// Bowling type, encoded as integer, see Utility.h for encodings

};


/**
 * @brief Storage for all detail describing a player
 * 
 * Stores all information needed to describe a player, including name, team and statistics. Values are stored privately and
 * accessed using getters, following typical OOP convention. Class also includes methods for formatting name (e.g. initials and last name,
 * full name, etc.), and getters for each statistic stored in the Stats object. 
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

/**
 * @brief 
 * @tparam T 
 * @param list 
 * @param len 
 * @param sort_val 
 * @return 
*/
template <typename T>
Player** sort_array(Player** list, int len, T (Player::*sort_val)() const);


/**
 * @brief Storage for a playing XI of Player objects
 * 
 * Stores 11 Player objects in order corresponding to a playing XI, and also includes team name and 
 * indices corresponding to specialist roles in the team. The XI is stored as a static array of 11 Player
 * pointers, ordered by the desired batting order (under standard conditions - see the functions get_nightwatch,
 * - in Simulation.h for situations where this batting order is changed). The team name is stored as a string, and
 * the struct also includes 4 integers storing indices pointing to the captain, wicketkeeper and the two opening 
 * bowlers in the playing XI array.
*/
struct Team {
	std::string name;
	Player* players[11];

	// Indexes refer to players array
	int i_captain;
	int i_wk;
	int i_bowl1;
	int i_bowl2;
};



/**
 * @brief Prints to the console a nicely formatted playing XI from a Team struct
 * @param os 
 * @param team 
 * @return 
 * @relatesals Team
*/
std::ostream& operator<<(std::ostream& os, const Team& team);

#endif // PLAYER_H