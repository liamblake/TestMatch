// -*- lsst-c++ -*-
/* FileIO.h
 *
 *
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "Cards.h"
#include "Player.h"
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

/* IMPORTANT NOTE:
    For this to work properly, any class which has members stored as pointers
    which are dynamically allocated at run-time MUST define a copy constructor
    and not use the default. Otherwise, we will get BIG memory problems.
*/
template <class T>
inline T* load_data(std::string filename) {

  // Create a temporary (static) object for loading
  T new_obj;

  // Create and open an archive for input
  std::ifstream ifs(filename);
  boost::archive::binary_iarchive ia(ifs);
  ia >> new_obj;

  // Create a dynamically allocated object
  T* dyn_obj = new T;
  *dyn_obj = new_obj;

  // This is a hacky solution
  return dyn_obj;
};

Player* csv2player(std::string line);
Venue* csv2venue(std::string line);
std::pair<Venue**, int>* load_venues(std::string dir = "data/venues.dat");

#endif // FILEIO_H