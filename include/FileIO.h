// -*- lsst-c++ -*-
/* FileIO.h
 *
 * 
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Player.h"
#include "Cards.h"
#include "Simulation.h"


template <class T>
inline void save_data(T* obj, std::string filename) {
    // Open character archive for output
    std::ofstream ofs(filename);

    // Save data 
    {
        boost::archive::binary_oarchive oa(ofs);
        oa << *obj;
    }
};

template <class T>
inline void load_data(T &new_obj, std::string filename) {

        // Create and open an archive for input
        std::ifstream ifs(filename);
        boost::archive::binary_iarchive ia(ifs);
        ia >> new_obj;

};



Player* csv2player(std::string line);
Venue* csv2venue(std::string line);
std::pair<Venue**, int>* load_venues(std::string dir = "data/venues.dat");


#endif // FILEIO_H