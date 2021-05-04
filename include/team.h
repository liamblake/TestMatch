// -*- lsst-c++ -*-
/* Player.h
 *
 * Interface for basic player storage types. Individual players and their
 * relevant career statistics
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "enums.h"

/**
 * @brief Storage for all career statistics of an individual player.
 *
 * These statistics are used to create predicitions and simulate
 * parts of the game.
 */
struct Stats {
    // Batting statistics
    /**
     * @brief The number of innings in which the player has batted over their
     * career.
     */
    int innings;
    /**
     * @brief Career batting average of the player (average runs per dismissal).
     */
    double bat_avg;
    /**
     * @brief Career batting strike rate of the player (average runs per 100
     * balls faced).
     */
    double bat_sr;

    // Bowling statistics
    /**
     * @brief The number of balls bowled by the player over their career.
     */
    int balls_bowled;
    /**
     * @brief Career bowling average of the player (average runs conceded
     * per wicket).
     */
    double bowl_avg;
    /**
     * @brief Career bowling strike rate of the player (average balls bowled per
     * wicket).
     */
    double bowl_sr;
    /**
     * @brief Career bowling economy of the player (average runs conceded per 6
     * balls bowled).
     */
    double bowl_econ;

    // General descriptors
    /**
     * @brief Batting hand of the player, as an enumeration with possible values
     * right or left.
     */
    Arm bat_arm;
    /**
     * @brief Bowling arm of the player, as an enumeration with possible values
     * right or left.
     */
    Arm bowl_arm;
    /**
     * @brief Bowling type of the player, as an enumeration.
     */
    BowlType bowl_type;

    // Serialisation method
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& innings;
        ar& bat_avg;
        ar& bat_sr;
        ar& balls_bowled;
        ar& bowl_avg;
        ar& bowl_sr;
        ar& bowl_econ;
        ar& bat_arm;
        ar& bowl_arm;
        ar& bowl_type;
    };
};

// Oh how I wish C++ had introspection
bool operator==(const Stats& lhs, const Stats& rhs);

/**
 * @brief Storage for all detail describing a player
 *
 * Stores all information needed to describe a player, including name, team and
 * statistics. Values are stored privately and accessed using getters, following
 * typical OOP convention. Class also includes methods for formatting name (e.g.
 * initials and last name, full name, etc.), and getters for each statistic
 * stored in the Stats object.
 */
class Player {
  private:
    /**
     * @brief First name of player to display on scorecard, e.g. Ellyse
     */
    std::string first_name;
    /**
     * @brief Surname of player to display on scorecard, e.g. Perry
     */
    std::string last_name;
    /**
     * @brief Initials excluding display surname, e.g. for EA to display EA
     * Perry on the scorecard.
     */
    std::string initials;

    /**
     * @brief Career statistics of the player.
     */
    Stats player_stats;

  public:
    // Default constructor
    Player(){};

    /**
     * @brief Construct a new Player object.
     *
     * @param c_first_name First name of the player, e.g. Steven.
     * @param c_last_name Last name of the player, e.g. Smith.
     * @param c_initials Initials of the player to display on the scorecard,
     * e.g. SPD.
     * @param stats Career statistics of the player.
     */
    Player(std::string c_first_name, std::string c_last_name,
           std::string c_initials, Stats stats);

    // Default destructor

    /** @defgroup player_name_getters Getters for the name of a player.
     * Methods for returning the player's name in various forms as a string.
     * @{
     */
    std::string get_initials() const;
    std::string get_last_name() const;

    std::string get_full_name() const;
    std::string get_full_initials() const;

    /** @} // end of player_name_getters */

    /** @defgroup player_stats_getters Getters for the career statistics of a
     * player Methods for returning the player's career statistics, which are
     * stored inside the Player class as a Stats object.
     * @{
     */
    Stats get_stats() const;
    int get_innings() const;
    double get_bat_avg() const;
    double get_bat_sr() const;
    int get_balls_bowled() const;
    double get_bowl_avg() const;
    double get_bowl_sr() const;
    double get_bowl_econ() const;
    Arm get_bat_arm() const;
    Arm get_bowl_arm() const;
    BowlType get_bowl_type() const;
    /** @} // end of player_stats_getters */

    // For dealing with cheating part-time bowlers
    void inflate_bowl_avg();

    // Serialisation methods
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& first_name;
        ar& last_name;
        ar& initials;
        ar& player_stats;
    };

    friend bool operator==(const Player& lhs, const Player& rhs);
};

/**
 * @brief Sorts a dynamic array of Player pointers by a passed statistic.
 * @tparam T Typename of statistic sorting by, return type of sort_val.
 * @param list Pointer to array of Player pointers to be sorted.
 * @param len Length of array to be sorted.
 * @param sort_val Function pointer to Player getter method of the desired
 * statistic to sort the array by.
 * @return Pointer to a NEW sorted array of Player pointers, of size len.
 * Dynamically allocated, must be deleted.
 */
template <typename T>
Player** sort_array(Player** list, int len, T (Player::*sort_val)() const);

/**
 * @brief Storage for a playing XI of Player objects
 *
 * Stores 11 Player objects in order corresponding to a playing XI, and also
 * includes team name and indices corresponding to specialist roles in the
 * team. The XI is stored as a static array of 11 Player pointers, ordered
 * by the desired batting order (under standard conditions - see the
 * functions get_nightwatch,
 * - in Simulation.h for situations where this batting order is changed).
 * The team name is stored as a string, and the struct also includes 4
 * integers storing indices pointing to the captain, wicketkeeper and the
 * two opening bowlers in the playing XI array.
 */
// Need to fix data encapsulation - make things private and have
// getters/setters
struct Team {

    std::string name;
    Player* players[11];

    // Indices refer to players array
    int i_captain;
    int i_wk;
    int i_bowl1;
    int i_bowl2;

    // Serialisation
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar << name;
        ar << players;
        ar << i_captain;
        ar << i_wk;
        ar << i_bowl1;
        ar << i_bowl2;
    };

    friend bool operator==(const Team& lhs, const Team& rhs);
};

#endif // PLAYER_H