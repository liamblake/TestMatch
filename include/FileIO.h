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
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Player.h"
#include "Cards.h"
#include "Simulation.h"


template <class T>
inline void save_data(T* obj, std::string filename) {
    // Open character archive for output
    std::ofstream ofs(filename);

    // Save data 
    {
        boost::archive::text_oarchive oa(ofs);
        //oa << *obj;
    }
};

template <class T>
inline T load_data(std::string filename) {
    // New object
    T newobj;
    {
        // Create and open an archive for input
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);

        ia >> newobj;
    }

    return newobj;
};



// Not sure if the following are used, hence the commenta
// Player* csv2player(std::string line);

// Team* load_team(std::string dir);
// void save_team(Team team, std::string dir);

// Venue* csv2venue(std::string line);

// std::pair<Venue**, int> load_venues(std::string dir = "data/venues.dat");


#endif // FILEIO_H