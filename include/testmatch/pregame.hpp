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

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& seam;
        ar& spin;
    };
};

/**
 * @brief Describes a venue and pitch conditions.
 */
struct Venue {
    std::string name;
    std::string city;
    std::string country;

    PitchFactors* pitch_factors;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& city;
        ar& country;
        ar& pitch_factors;
    };
};

struct Pregame {
    Venue* venue;
    Team* home_team;
    Team* away_team;
};

struct TossResult {
    Team* winner;
    Team* loser;
    TossChoice choice;

    Team* get_bat_team();
    Team* get_bowl_team();

    /**
     * @brief Cast to standard library string type.
     *
     * @return std::string
     */
    operator std::string();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& winner;
        ar& loser;
        ar& choice;
    };
};

#endif // PREGAME_H