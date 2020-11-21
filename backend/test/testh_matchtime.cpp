#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>

#include <string>

#include "MatchTime.h"

using boost::test_tools::output_test_stream;
//using namespace boost::unit_test;

// Example objects for testing


BOOST_AUTO_TEST_SUITE(test_header_time)

void check_ostream(output_test_stream& output, int length, std::string expected) {
    BOOST_TEST(!output.is_empty(false));
    BOOST_TEST(output.check_length(length, false));
    BOOST_TEST(output.is_equal(expected));
}

BOOST_AUTO_TEST_CASE(testclass_time_constructs) {
    // For verifying output stream
    output_test_stream os;
    
    // Constructors for Time
    Time tc();
    os << tc;
    check_ostream(os, 10, "12:00:00 am");


    Time tc();


}

BOOST_AUTO_TEST_CASE(testclass_time_operators) {

}


BOOST_AUTO_TEST_CASE(testclass_time_setters) {

}

BOOST_AUTO_TEST_SUITE_END()