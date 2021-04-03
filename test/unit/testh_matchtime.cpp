#define BOOST_TEST_DYN_LINK

#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

#include <string>

#include "MatchTime.h"

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

    TimeOfDay t3(59, 59, 23);
    BOOST_TEST(t3.sec() == 23);
    BOOST_TEST(t3.min() == 59);
    BOOST_TEST(t3.hrs() == 59);

    // Double constructor
    TimeOfDay t4(7.35);
    BOOST_TEST(t4.sec() == 0);
    BOOST_TEST(t4.min() == 35);
    BOOST_TEST(t4.hrs() == 7);

    TimeOfDay t5(17.05);
    BOOST_TEST(t5.sec() == 0);
    BOOST_TEST(t5.min() == 5);
    BOOST_TEST(t5.hrs() == 17);

    // Constructors with rounding
    TimeOfDay t6(5, 61, 24);
    BOOST_TEST(t6.sec() == 5);
    BOOST_TEST(t6.min() == 1);
    BOOST_TEST(t6.hrs() == 1);

    TimeOfDay t7(3, 2, 78);
    BOOST_TEST(t7.sec() == 3);
    BOOST_TEST(t7.min() == 2);
    BOOST_TEST(t7.hrs() == 6);

    TimeOfDay t8(29.72);
    BOOST_TEST(t8.sec() == 0);
    BOOST_TEST(t8.min() == 12);
    BOOST_TEST(t8.hrs() == 6);
}

BOOST_AUTO_TEST_CASE(testclass_timeofday_operators) {
    TimeOfDay t1;

    // Casts
    // BOOST_TEST(std::string(t1) == "00:00:00");
}

BOOST_AUTO_TEST_SUITE_END()