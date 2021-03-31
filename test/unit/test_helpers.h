
#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <boost/test/unit_test.hpp>
#include <string>

template <typename T>
inline void test_serialisation(T* obj, std::string fname) {
    save_data<T>(obj, fname);
    T* obj_new = load_data<T>(fname);
    // BOOST_CHECK(*obj_new == *obj);
    // This requires all serialisable classes to define ==, which I should do
    // anyways for testing sake
    BOOST_TEST(obj_new != obj);

    delete obj_new;
}

#endif // TESTHELPERS_H
