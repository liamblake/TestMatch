#ifndef PREGAME_H
#define PREGAME_H

#include "enums.hpp"
#include "team.hpp"

#include <string>

/**
 * @brief
 */
struct PitchFactors {
    double seam;
    double spin;
};

/**
 * @brief Describes a venue and pitch conditions.
 */
struct Venue {
    /**
     * @brief
     *
     */
    std::string name;
    /**
     * @brief
     *
     */
    std::string city;
    /**
     * @brief
     *
     */
    std::string country;

    /**
     * @brief
     *
     */
    PitchFactors* pitch_factors;
};

struct Pregame {
    /**
     * @brief
     *
     */
    Venue* venue;
    /**
     * @brief
     *
     */
    Team* home_team;
    /**
     * @brief
     *
     */
    Team* away_team;
};

struct TossResult {
    Team* winner;
    Team* loser;
    TossChoice choice;

    /**
     * @brief Get the pointer to the team that is batting first.
     *
     * @return Team*
     */
    Team* get_bat_team();
    /**
     * @brief Get the bowl team object
     *
     * @return Team*
     */
    Team* get_bowl_team();

    /**
     * @brief Cast to standard library string type.
     *
     * @return std::string
     */
    operator std::string();
};

#endif // PREGAME_H