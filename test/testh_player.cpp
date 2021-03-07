#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
//#include <boost/mpl/list.hpp>

#include <string>

#include "Player.h"
#include "FileIO.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_header_player)

//BOOST_AUTO_TEST_CASE(testclass_overcount) {
//	// Default initialisation
//	OverCount oc;
//
//	BOOST_TEST(oc.as_balls() == 0);
//	BOOST_TEST(std::string(oc) == "0.0");
//	BOOST_TEST(float(oc) == 0.0);
//
//	// Iterator operands
//	BOOST_TEST((++oc).as_balls() == 1);
//	BOOST_TEST((oc++).as_balls() == 1);
//	BOOST_TEST(oc.as_balls() == 2);
//
//	// Other constructor
//	OverCount oc2 (7,4);
//	BOOST_TEST(oc2.as_balls() == 46);
//	BOOST_TEST(std::string(oc2) == "7.4");
//	BOOST_TEST(float(oc2) == 7.4f);
//
//}

BOOST_AUTO_TEST_CASE(testclass_player) {

	Player tp_bat("Marnus", "Labuschagne", "M", { 23, 63.43, 56.52, 756, 38.66,  63.0, 3.68, false, 5 });

	BOOST_TEST(tp_bat.get_initials() == "M");
	BOOST_TEST(tp_bat.get_full_initials() == "M Labuschagne");
	BOOST_TEST(tp_bat.get_last_name() == "Labuschagne");
	BOOST_TEST(tp_bat.get_full_name() == "Marnus Labuschagne");

	BOOST_TEST(tp_bat.get_innings() == 23);
	BOOST_TEST(tp_bat.get_bat_avg() == 63.43);
	BOOST_TEST(tp_bat.get_bat_sr() == 56.52);

	BOOST_TEST(tp_bat.get_balls_bowled() == 756);
	BOOST_TEST(tp_bat.get_bowl_avg() == 38.66);
	BOOST_TEST(tp_bat.get_bowl_sr() == 63.0);
	BOOST_TEST(tp_bat.get_bowl_econ() == 3.68);

	BOOST_TEST(tp_bat.get_bat_hand() == false);
	BOOST_TEST(tp_bat.get_bowl_type() == 5);

	// Test serialisation
	save_data<Player>(&tp_bat, "test/test_loosebuschange.tmpl");
	Player* tp_new = load_data<Player>("test_loosebuschange.tmpl");
	BOOST_TEST(*tp_new == tp_bat);
	BOOST_TEST(tp_new != &tp_bat);

	delete tp_new;


}



BOOST_AUTO_TEST_SUITE_END()