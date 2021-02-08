// -*- lsst-c++ -*-
/* TestHelpers.h
 *
 *
*/

#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include "Player.h"

// Tests whether a given player contains all expected values
inline void test_player_values(Player* player, std::string exp_first_name, std::string exp_last_name, std::string exp_initials, Stats exp_stats, std::string exp_team) {
	BOOST_TEST(player->get_initials() == exp_initials);
	BOOST_TEST(player->get_full_initials() == exp_initials + " " + exp_last_name);
	BOOST_TEST(player->get_last_name() == exp_last_name);
	BOOST_TEST(player->get_full_name() == exp_first_name + exp_last_name);

	BOOST_TEST(player->get_team() == exp_team);

	BOOST_TEST(player->get_innings() == exp_stats.innings);
	BOOST_TEST(player->get_bat_avg() == exp_stats.bat_avg);
	BOOST_TEST(player->get_bat_sr() == exp_stats.bat_sr);

	BOOST_TEST(player->get_balls_bowled() == exp_stats.balls_bowled);
	BOOST_TEST(player->get_bowl_avg() == exp_stats.bowl_avg);
	BOOST_TEST(player->get_bowl_sr() == exp_stats.bowl_sr);
	BOOST_TEST(player->get_bowl_econ() == exp_stats.bowl_econ);

	BOOST_TEST(player->get_bat_hand() == exp_stats.bat_hand);
	BOOST_TEST(player->get_bowl_type() == exp_stats.bowl_type);
}

class Tester {


  public:

	  virtual bool run_tests() = 0;
};


/* Test classes, allowing testing of specific and private components
*/
class TestDelivery : public Tester {

};

class TestBattingLineup : public Tester {

};

class TestBowlingLineup : public Tester {

};

#endif