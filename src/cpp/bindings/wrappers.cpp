
//#include <boost/python.hpp>
#include <pybind11/pybind11.h>
#include <testmatch/cards.hpp>
#include <testmatch/matchtime.hpp>
#include <testmatch/pregame.hpp>
#include <testmatch/simulation.hpp>
#include <testmatch/team.hpp>

using namespace pybind11;

PYBIND11_MODULE(_testmatch, m) {
    // Enumerations

    // These are mirrored by Python dataclasses for more intuitive input, and
    // coerced into these C++ types prior to simulation.
    class_<Stats>(m, "_Stats");
    class_<Player>(m, "_Player");
    class_<Team>(m, "_Team");
    class_<PitchFactors>(m, "_PitchFactors");
    class_<Venue>(m, "_Venue");
    class_<Pregame>(m, "_Pregame");

    // These objects are exposed to the public Python library, since the
    // elements should not be modified manually.
    // class_<BatterCard>("BatterCard");
    // class_<BowlerCard>("BowlerCard");

    // These objects are used within the simulation and not exposed in the
    // public Python library.
    // class_<BattingManager>("_BattingManager");
    // class_<BowlingManager>("_BowlingManager");
    // class_<FieldingManager>("_FieldingManager");
    // class_<MatchTime>("_MatchTime");

    // The simulation objects will be extended in Python
    // class_<Innings>("Innings");
    // class_<Match>("Match");
}