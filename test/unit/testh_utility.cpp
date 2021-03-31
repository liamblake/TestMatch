#define BOOST_TEST_DYN_LINK

#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>
//#include <boost/mpl/list.hpp>

#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Utility.h"

BOOST_AUTO_TEST_SUITE(test_header_utility)

BOOST_AUTO_TEST_CASE(testfunc_split_str) {
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
    BOOST_TEST(split_str("1thisisadelimeter2thisisadelimeter3",
                         "thisisadelimeter") == expected);
}

BOOST_AUTO_TEST_CASE(testfunc_balls_to_ov) {
    std::pair<int, int> out = balls_to_ov(0);
    BOOST_TEST((out.first == 0) & (out.second == 0));

    out = balls_to_ov(1);
    BOOST_TEST((out.first == 0) & (out.second == 1));

    out = balls_to_ov(6);
    BOOST_TEST((out.first == 1) & (out.second == 0));

    out = balls_to_ov(11);
    BOOST_TEST((out.first == 1) & (out.second == 5));

    out = balls_to_ov(7);
    BOOST_TEST((out.first == 1) & (out.second == 1));

    out = balls_to_ov(480);
    BOOST_TEST((out.first == 80) & (out.second == 0));
}

BOOST_AUTO_TEST_CASE(testfunc_is_slow_bowler) {
    std::string types[12] = {"rm", "rmf", "rfm", "rf", "ob",  "lb",
                             "lm", "lmf", "lfm", "lf", "slo", "slu"};
    bool expected[12] = {true, false, false, false, true, true,
                         true, false, false, false, true, true};

    for (int i = 0; i < 12; i++) {
        BOOST_TEST(is_slow_bowler(encode_bowltype(types[i])) == expected[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()