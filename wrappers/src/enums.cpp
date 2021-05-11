#include <boost/python/enum.hpp>
#include <boost/python/module.hpp>
#include <enums.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(_testmatch) {
    enum_<Arm>("Arm").value("left", left).value("right", right).export_values();

    enum_<BowlType>("BowlType")
        .value("med", med)
        .value("med_fast", med_fast)
        .value("fast_med", fast_med)
        .value("fast", fast_med)
        .value("offbreak", offbreak)
        .value("legbreak", legbreak)
}