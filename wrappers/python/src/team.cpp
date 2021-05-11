#include <boost/python.hpp>
#include <team.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(_testmatch) {
    class_<Stats>("_Stats");
    class_<Player>("_Player");
}
