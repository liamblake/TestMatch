#define BOOST_TEST_DYN_LINK

#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>

#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

#define private                                                                \
 public // This is a hack and immensely evil, but lets me test private methods
        // easily
#include "Cards.h"
#include "Player.h"
#include "Simulation.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_header_simulation)

// This is going to be a long one...

// Test teams (pun intended)
Player a1("David", "Warner", "DA",
          {155, 48.94, 72.85, 342, 67.25, 85.5, 4.71, true, 5});
Player a2("Will", "Pucovski", "WJ",
          {1, 42.54, 60.21, 0, 1000, 1000, 4.00, false, 0});
Player a3("Marnus", "Labuschagne", "M",
          {23, 63.43, 56.52, 756, 38.66, 63.0, 3.68, false, 5});
Player a4("Steve", "Smith", "SPD",
          {131, 62.84, 55.3, 1381, 56.47, 81.2, 4.17, false, 5});
Player a5("Travis", "Head", "TM",
          {28, 41.96, 50.41, 126, 68.32, 63.7, 3.61, true, 4});
Player a6("Cameron", "Green", "C",
          {7, 40.71, 40.68, 264, 30.30, 50.7, 2.98, false, 2});
Player a7("Tim", "Paine", "TD",
          {50, 31.66, 44.24, 0, 1000, 1000, 4.00, false, 0});
Player a8("Pat", "Cummins", "PJ",
          {44, 17.02, 38.51, 6761, 21.82, 47.2, 2.76, false, 2});
Player a9("Jhye", "Richardson", "JA",
          {1, 12.95, 58.81, 306, 23.74, 52.3, 2.41, false, 3});
Player a10("Josh", "Hazlewood", "JR",
           {68, 12.02, 45.22, 11887, 25.65, 56.0, 2.74, true, 2});
Player a11("Nathan", "Lyon", "NM",
           {123, 12.27, 46.99, 24568, 31.58, 62.9, 3, false, 4});
Team aus = {"Australia", &a1, &a2,  &a3,  &a4, &a5, &a6, &a7,
            &a8,         &a9, &a10, &a11, 6,   6,   9,   8};

Player b1("Tom", "Latham", "TWM",
          {92, 42.34, 46.66, 0, 1000, 1000, 4.00, true, 0});
Player b2("Tom", "Blundell", "TA",
          {11, 47.22, 49.47, 18, 1000, 1000, 4.33, false, 4});
Player b3("Kane", "Williamson", "KS",
          {140, 50.99, 51.63, 2103, 40.62, 72.5, 3.36, false, 4});
Player b4("Ross", "Taylor", "LRPL", {178, 46.1, 60, 96, 24, 48, 3, false, 4});
Player b5("Henry", "Nicholls", "HM",
          {50, 39.7, 49.39, 0, 1000, 1000, 4.00, true, 4});
Player b6("BJ", "Watling", "BJ",
          {110, 38.5, 42.35, 0, 1000, 1000, 4.00, true, 0});
Player b7("Mitchell", "Santner", "MJ",
          {29, 25.55, 42.36, 3746, 44.71, 96, 2.79, true, 10});
Player b8("Kyle", "Jamieson", "KA",
          {6, 21.47, 55, 1202, 21.14, 42.2, 3, false, 1});
Player b9("Tim", "Southee", "TG",
          {106, 17.37, 85.84, 16393, 29, 57.7, 3.01, false, 1});
Player b10("Neil", "Wagner", "N",
           {63, 12.5, 44.88, 10743, 26.6, 52.1, 3.06, true, 7});
Player b11("Trent", "Boult", "TA",
           {82, 15.2, 56.86, 14874, 27.65, 55.7, 2.97, false, 7});
Team nz = {"New Zealand", &b1, &b2,  &b3,  &b4, &b5, &b6, &b7,
           &b8,           &b9, &b10, &b11, 2,   5,   10,  8};

// Venue
PitchFactors lords_pf = {0.75995148, 0.24004852};
Venue lords = {"Lords", "London", "ENG", &lords_pf};

BOOST_AUTO_TEST_CASE(testclass_battingmanager) {
  // Create batting cards for each player
  BatterCard** cards = create_batting_cards(&aus);

  for (int i = 0; i < 11; i++) {
    delete cards[i];
  }
}

BOOST_AUTO_TEST_CASE(testclass_innings) {
  // Create an innings
  Innings inns(&aus, &nz, 0, &lords_pf);

  // Check initialisation of innings
  BOOST_TEST(inns.striker->get_player_ptr() == &a1 |
             inns.striker->get_player_ptr() == &a2);
  BOOST_TEST(inns.nonstriker->get_player_ptr() == &a1 |
             inns.nonstriker->get_player_ptr() == &a2);
  BOOST_TEST(inns.striker != inns.nonstriker);

  BOOST_TEST(inns.bowl1->get_player_ptr() == &b11);
  BOOST_TEST(inns.bowl2->get_player_ptr() == &b9);

  // Simulate a delivery
}

BOOST_AUTO_TEST_CASE(testfeature_followon) {

  // Cases where follow-on is not an option
  BOOST_CHECK(!Match::DECIDE_FOLLOW_ON(0));
  BOOST_CHECK(!Match::DECIDE_FOLLOW_ON(-201));
  BOOST_CHECK(!Match::DECIDE_FOLLOW_ON(199));

  // Ensure fit matches that expected by R
  double eps = 0.0001;
  BOOST_TEST(abs(Match::MODEL_FOLLOW_ON(200) - 0.1386838) < eps);
  BOOST_TEST(abs(Match::MODEL_FOLLOW_ON(250) - 0.3812311) < eps);
  BOOST_TEST(abs(Match::MODEL_FOLLOW_ON(350) - 0.7442012) < eps);
  BOOST_TEST(abs(Match::MODEL_FOLLOW_ON(500) - 0.9046413) < eps);
}

BOOST_AUTO_TEST_SUITE_END()