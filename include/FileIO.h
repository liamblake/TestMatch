// -*- lsst-c++ -*-
/* FileIO.h
 *
 * 
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>
#include <utility>

#include "Player.h"
#include "Cards.h"
#include "Simulation.h"

// Rudimentary representation of match scorecard, for saving/loading file
struct ScorecardData {
    // Needs a corresponding match object
    Match* match;
};

// Rudimentary representation of ball-by-ball
struct BallByBall {
    // Needs a corresponding match object
    Match* match;

};

Player* csv2player(std::string line);

Team* load_team(std::string dir);
void save_team(Team team, std::string dir);

Venue* csv2venue(std::string line);

std::pair<Venue**, int> load_venues(std::string dir = "data/venues.dat");


#endif // FILEIO_H