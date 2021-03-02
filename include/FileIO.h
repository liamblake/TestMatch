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


template <class T>
void save_data(T* obj, std::string filename);

template <class T>
T* load_data(std::string filename);


// Not sure if the following are used, hence the commenta
// Player* csv2player(std::string line);

// Team* load_team(std::string dir);
// void save_team(Team team, std::string dir);

// Venue* csv2venue(std::string line);

// std::pair<Venue**, int> load_venues(std::string dir = "data/venues.dat");


#endif // FILEIO_H