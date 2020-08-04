#define BOOST_TEST_MODULE autotest

#include <boost/test/included/unit_test.hpp>
//#include <boost/mpl/list.hpp>

#include <iostream>
#include <string>
#include <utility>

#include "Player.h"
#include "Utility.h"
#include "Cards.h"

BOOST_AUTO_TEST_CASE(testclass_player)
{
  // Test player
	Stats m_stats = { 23, 63.43, 56.52, 756, 38.66,  63.0, 3.68, false, 0};
	//m_stats.innings = 23;
	//m_stats.bat_avg = 63.43;
	//m_stats.bat_sr = 56.52;

	//m_stats.balls_bowled = 756;
	//m_stats.bowl_avg = 38.66;
	//m_stats.bowl_sr = 63.0;
	//m_stats.bowl_econ = 3.68;

	//m_stats.bat_hand = false;
	//m_stats.bowl_type = 0;

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

//template <class T>
//bool equals(T* rhs, T* lhs, int len) {
//	for (int i = 0; i < len; i++) {
//		if (rhs[i] != lhs[i]) {
//			return false;
//		}
//	}
//
//	return true;
//};

// arr_add_item - template function
//typedef boost::mpl::list<int, int*, double, std::string> test_types;
//BOOST_AUTO_TEST_CASE_TEMPLATE(testfunc_add_arr_item, T, test_types) {
//	// Boundary case - empty array
//	T* old;
//	T* expected = new T[1];
//	expected[0] = T(1);
//
//	BOOST_TEST(equals(arr_add_item<T>(old, 0, T(1)), expected, 1));
//}


BOOST_AUTO_TEST_CASE(testfunc_split_str)
{
	std::vector<std::string> expected;

	// Boundary case - empty string
	BOOST_TEST(split_str("").empty());

	// Boundary case - just delimeter
	expected.push_back("");
	expected.push_back("");
	BOOST_TEST(split_str(",") == expected);
	expected.clear();

	// Boundary case - no delimeter
	expected.push_back("test");
	BOOST_TEST(split_str("test") == expected);
	expected.clear();

	// Standard case - default delimeter
	expected.push_back("a");
	expected.push_back("b");
	expected.push_back("c");
	BOOST_TEST(split_str("a,b,c") == expected);

	// Standard case - delimeter at end
	expected.push_back("");
	BOOST_TEST(split_str("a,b,c,") == expected);

	// Standard case - delimeter at start
	expected.pop_back();
	expected.insert(expected.begin(), "");
	BOOST_TEST(split_str(",a,b,c") == expected);
	expected.clear();

	// Standard case - other delimeter
	expected.push_back("1");
	expected.push_back("2");
	expected.push_back("3");
	BOOST_TEST(split_str("1 2 3", " ") == expected);

	// Standard case - other delimeter
	BOOST_TEST(split_str("1thisisadelimeter2thisisadelimeter3", "thisisadelimeter") == expected);
}




BOOST_AUTO_TEST_CASE(testclass_battercard) {
	// Test object
	Stats m_stats = { 23, 63.43, 56.52, 756, 38.66,  63.0, 3.68, false, 0 };;
	Player p("Marnus", "Labuschagne", "M", m_stats, "Australia");
	BatterCard bc(&p);

	// Ensure correct initialisation
	BOOST_TEST(bc.print_card() == "M Labuschagne not out 0 (0b 0x4 0x6) SR: -");

	// Use array of pairs to test outcomes
	std::pair<std::string, std::string> outcomes[18];
	outcomes[0] = { "0", "M Labuschagne not out 0 (1b 0x4 0x6) SR: 0.00" };
	outcomes[1] = { "1", "M Labuschagne not out 1 (2b 0x4 0x6) SR: 50.00" };
	outcomes[2] = { "2", "M Labuschagne not out 3 (3b 0x4 0x6) SR: 100.00" };
	outcomes[3] = { "3", "M Labuschagne not out 6 (4b 0x4 0x6) SR: 150.00" };
	outcomes[4] = { "4", "M Labuschagne not out 10 (5b 1x4 0x6) SR: 200.00" };
	outcomes[5] = { "5", "M Labuschagne not out 15 (6b 2x4 0x6) SR: 250.00" };
	outcomes[6] = { "6", "M Labuschagne not out 21 (7b 2x4 1x6) SR: 300.00" };
	outcomes[7] = { "1nb", "M Labuschagne not out 21 (8b 2x4 1x6) SR: 262.50" };
	outcomes[8] = { "2nb", "M Labuschagne not out 22 (9b 2x4 1x6) SR: 244.44" };
	outcomes[9] = { "5nb", "M Labuschagne not out 26 (10b 3x4 1x6) SR: 260.00" };
	outcomes[10] = { "7nb", "M Labuschagne not out 32 (11b 3x4 2x6) SR: 290.91" };
	outcomes[11] = { "0lb", "M Labuschagne not out 32 (12b 3x4 2x6) SR: 266.67" };
	outcomes[12] = { "1lb", "M Labuschagne not out 32 (13b 3x4 2x6) SR: 246.15" };
	outcomes[13] = { "4lb", "M Labuschagne not out 32 (14b 3x4 2x6) SR: 228.57" };
	outcomes[14] = { "0b", "M Labuschagne not out 32 (15b 3x4 2x6) SR: 213.33" };
	outcomes[15] = { "1b", "M Labuschagne not out 32 (16b 3x4 2x6) SR: 200.00" };
	outcomes[16] = { "4b", "M Labuschagne not out 32 (17b 3x4 2x6) SR: 188.24" };
	outcomes[17] = { "1w", "M Labuschagne not out 32 (17b 3x4 2x6) SR: 188.24" };




	for (int i = 0; i < 18; i++) {
		bc.update_score(outcomes[i].first);
		BOOST_TEST(bc.print_card() == outcomes[i].second);
	}

}