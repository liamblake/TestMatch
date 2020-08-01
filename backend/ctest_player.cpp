#define BOOST_TEST_MODULE ctestPlayer
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "Player.h"

BOOST_AUTO_TEST_CASE(player_std)
{
  // Test player
	Stats m_stats;
	m_stats.innings = 23;
	m_stats.bat_avg = 63.43;
	m_stats.bat_sr = 56.52;

	m_stats.balls_bowled = 756;
	m_stats.bowl_avg = 38.66;
	m_stats.bowl_sr = 63.0;
	m_stats.bowl_econ = 3.68;

	m_stats.bat_hand = false;
	m_stats.bowl_type = 0;

	Player p("Marnus", "Labuschagne", "M", m_stats, "Australia");

	BOOST_TEST(p.get_initials() == "M");
	BOOST_TEST(p.get_full_initials() == "M Labuschagne");
	BOOST_TEST(p.get_last_name() == "Labuschagne");
	BOOST_TEST(p.get_full_name() == "Marnus Labuschagne");

	BOOST_TEST(p.get_team() == "Australia");

	BOOST_TEST(p.get_innings() == 23);
	BOOST_TEST(p.get_bat_avg() == 63.43);
	BOOST_TEST(p.get_bat_sr() == 56.52);

	BOOST_TEST(p.get_balls_bowled() == 756);
	BOOST_TEST(p.get_bowl_avg() == 38.66);
	BOOST_TEST(p.get_bowl_sr() == 63.0);
	BOOST_TEST(p.get_bowl_econ() == 3.68);

	BOOST_TEST(p.get_bat_hand() == false);
	BOOST_TEST(p.get_bowl_type() == 0);

}

BOOST_AUTO_TEST_CASE(player_std)
{
  // Test player
	Stats m_stats;
	m_stats.innings = 23;
	m_stats.bat_avg = 63.43;
	m_stats.bat_sr = 56.52;

	m_stats.balls_bowled = 756;
	m_stats.bowl_avg = 38.66;
	m_stats.bowl_sr = 63.0;
	m_stats.bowl_econ = 3.68;

	m_stats.bat_hand = false;
	m_stats.bowl_type = 0;

	Player p("Marnus", "Labuschagne", "M", m_stats, "Australia");

	BOOST_TEST(p.get_initials() == "M");
	BOOST_TEST(p.get_full_initials() == "M Labuschagne");
	BOOST_TEST(p.get_last_name() == "Labuschagne");
	BOOST_TEST(p.get_full_name() == "Marnus Labuschagne");

	BOOST_TEST(p.get_team() == "Australia");

	BOOST_TEST(p.get_innings() == 23);
	BOOST_TEST(p.get_bat_avg() == 63.43);
	BOOST_TEST(p.get_bat_sr() == 56.52);

	BOOST_TEST(p.get_balls_bowled() == 756);
	BOOST_TEST(p.get_bowl_avg() == 38.66);
	BOOST_TEST(p.get_bowl_sr() == 63.0);
	BOOST_TEST(p.get_bowl_econ() == 3.68);

	BOOST_TEST(p.get_bat_hand() == false);
	BOOST_TEST(p.get_bowl_type() == 0);

}