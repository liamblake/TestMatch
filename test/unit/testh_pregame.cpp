#define BOOST_TEST_MODULE testPregame
#define BOOST_TEST_DYN_LINK

#include "fixtures.hpp"

#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>
#include <testmatch/enums.hpp>
#include <testmatch/pregame.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_tossresult)

// Fixtures
struct F : public F_TeamAus, F_TeamNZ {
    F() {
        ts1 = {&nz, &aus, bat};
        ts2 = {&nz, &aus, field};
    };
    ~F(){};

    TossResult ts1, ts2;
};

BOOST_FIXTURE_TEST_CASE(test_getters, F) {
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