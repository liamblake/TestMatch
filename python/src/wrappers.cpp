
#include <boost/python.hpp>
#include <testmatch/team.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(_testmatch) {
    class_<Stats>("_Stats").def_readwrite("innings", &Stats::innings);
}