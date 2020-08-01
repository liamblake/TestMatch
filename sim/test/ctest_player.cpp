#define BOOST_TEST_MODULE testPlayer
#include <boost/test/unit_test.hpp>

#include "Player.h"

using namespace boost::unit_test

BOOST_AUTO_TEST_CASE(player_test)
{
    Stats e_stats;
    Player test_object("", "", "", e_stats);

    BOOST_CHECK(true);
}