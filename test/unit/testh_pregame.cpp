#define BOOST_TEST_MODULE testPregame
#define BOOST_TEST_DYN_LINK

#include "fixtures.hpp"

#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>
#include <testmatch/enums.hpp>
#include <testmatch/pregame.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_tossresult)

// Test teams (pun intended)
Player b1("Tom", "Latham", "TWM",
          {92, 42.34, 46.66, 0, 1000, 1000, 4.00, left, left, med});
Player b2("Tom", "Blundell", "TA",
          {11, 47.22, 49.47, 18, 1000, 1000, 4.33, right, right, offbreak});
Player b3("Kane", "Williamson", "KS",
          {140, 50.99, 51.63, 2103, 40.62, 72.5, 3.36, right, right, offbreak});
Player b4("Ross", "Taylor", "LRPL",
          {178, 46.1, 60, 96, 24, 48, 3, right, right, offbreak});
Player b5("Henry", "Nicholls", "HM",
          {50, 39.7, 49.39, 0, 1000, 1000, 4.00, left, right, offbreak});
Player b6("BJ", "Watling", "BJ",
          {110, 38.5, 42.35, 0, 1000, 1000, 4.00, right, right, med});
Player b7("Mitchell", "Santner", "MJ",
          {29, 25.55, 42.36, 3746, 44.71, 96, 2.79, left, left, legbreak});
Player b8("Kyle", "Jamieson", "KA",
          {6, 21.47, 55, 1202, 21.14, 42.2, 3, right, right, fast_med});
Player b9("Tim", "Southee", "TG",
          {106, 17.37, 85.84, 16393, 29, 57.7, 3.01, right, right, med_fast});
Player b10("Neil", "Wagner", "N",
           {63, 12.5, 44.88, 10743, 26.6, 52.1, 3.06, left, left, med_fast});
Player b11("Trent", "Boult", "TA",
           {82, 15.2, 56.86, 14874, 27.65, 55.7, 2.97, right, left, fast_med});
Team nz = {"New Zealand", &b1, &b2,  &b3,  &b4, &b5, &b6, &b7,
           &b8,           &b9, &b10, &b11, 2,   5,   10,  8};

// Fixtures
struct F {
    F() {
        ts1 = {&nz, &aus, bat};
        ts2 = {&nz, &aus, field};
    };
    ~F(){};

    TossResult ts1, ts2;
};

BOOST_FIXTURE_TEST_CASE(test_getters) {
    BOOST_TEST(ts1.get_bat_team() == &nz);
    BOOST_TEST(ts1.get_bowl_team() == &aus);

    BOOST_TEST(ts2.get_bat_team() == &aus);
    BOOST_TEST(ts2.get_bowl_team() == &nz);
}

BOOST_FIXTURE_TEST_CASE(test_string, F) {
    BOOST_TEST(std::string(ts1) ==
               "New Zealand won the toss and elected to bat");
    BOOST_TEST(std::string(ts2) ==
               "New Zealand won the toss and elected to field");
}

BOOST_AUTO_TEST_SUITE_END()