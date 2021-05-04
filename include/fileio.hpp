// -*- lsst-c++ -*-
/* fileio.hpp
 *
 *
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "cards.hpp"
#include "simulation.hpp"
#include "team.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>
#include <string>

/**
 *
 * @brief Saves a serialisable object to a chosen directory, in a binary format.
 *
 * To be serialisable, a class must define a default constructor (with no
 * arguments) and either a template function called, or template methods called
 * load and save. See the Boost Serialization documentation for more detail.
 *
 * @tparam T Class type to be serialised, see above requirements.
 * @param obj Pointer to the object to be serialised.
 * @param dir Directory to save the serialised object to.
 */
template <class T>
inline void save_data(T* obj, std::string dir) {
    // Open character archive for output
    std::ofstream ofs(dir);

    // Save data
    boost::archive::binary_oarchive oa(ofs);
    oa << *obj;
};

/**
 * @brief Loads a serialised object saved in a file, in a binary format.
 *
 * NOTE: For this to work properly, any class which has members stored as
 * pointers which are dynamically allocated at run-time MUST define a copy
 * constructor and not use the default. Otherwise, we will get BIG memory
 * problems.
 *
 * @tparam T Class type to be loaded, which must meet the aforementioned
 * requirements.
 * @param dir Directory of the serialised object, saved in binary format.
 * @return T* Pointer to the loaded object, which has been allocated on the heap
 * via new.
 */
template <class T>
inline T* load_data(std::string dir) {

    // Create a temporary (static) object for loading
    T new_obj;

    // Create and open an archive for input
    std::ifstream ifs(dir);
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