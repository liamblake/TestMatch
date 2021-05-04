#define BOOST_TEST_DYN_LINK

#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

#include <string>

#include "matchtime.h"

BOOST_AUTO_TEST_SUITE(test_header_matchtimetime)

BOOST_AUTO_TEST_CASE(testclass_timeofday_constructors) {
    // Default constructor
    TimeOfDay t1;
    BOOST_TEST(t1.sec() == 0);
    BOOST_TEST(t1.min() == 0);
    BOOST_TEST(t1.hrs() == 0);

    // hrs, sec, min constructor
    TimeOfDay t2(1, 2, 3);
    BOOST_TEST(t2.sec() == 1);
    BOOST_TEST(t2.min() == 2);
    BOOST_TEST(t2.hrs() == 3);

    // Float constructor
}

BOOST_AUTO_TEST_CASE(testclass_timeofday_setters) {}

BOOST_AUTO_TEST_CASE(testclass_timeofday_operators) {
    TimeOfDay t1;

    // Casts
    // BOOST_TEST(std::string(t1) == "00:00:00");
}

BOOST_AUTO_TEST_SUITE_END()