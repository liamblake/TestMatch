
#include <pybind11/pybind11.h>
#include <testmatch/cards.hpp>
#include <testmatch/enums.hpp>
#include <testmatch/matchtime.hpp>
#include <testmatch/pregame.hpp>
#include <testmatch/simulation.hpp>
#include <testmatch/team.hpp>

using namespace pybind11;

PYBIND11_MODULE(_testmatch, m) {
    // Enumerations
    enum_<Arm>(m, "Arm")
        .value("left", left)
        .value("right", right)
        .export_values();

    enum_<BowlType>(m, "BowlType")
        .value("med", med)
        .value("med_fast", med_fast)
        .value("fast_med", fast)
        .value("offbreak", offbreak)
        .value("legbreak", legbreak)
        .export_values()
        .export_values();

    enum_<DismType>(m, "DismType")
        .value("bowled", bowled)
        .value("lbw", lbw)
        .value("caught", caught)
        .value("c_and_b", c_and_b)
        .value("run_out", run_out)
        .value("stumped", stumped)
        .export_values();

    enum_<ResultType>(m, "ResultType")
        .value("draw", draw)
        .value("win_chasing", win_chasing)
        .value("win_bowling", win_bowling)
        .value("win_innings", win_innings)
        .value("tie", tie)
        .export_values();

    enum_<TossChoice>(m, "TossChoice")
        .value("bat", bat)
        .value("field", field)
        .export_values();

    // These are mirrored by Python dataclasses for more intuitive input,
    // and coerced into these C++ types prior to simulation.
    class_<Stats>(m, "_Stats");
    class_<Player>(m, "_Player");
    class_<Team>(m, "_Team");
    class_<PitchFactors>(m, "_PitchFactors");
    class_<Venue>(m, "_Venue");
    class_<Pregame>(m, "_Pregame");

    // These objects are exposed to the public Python library, since the
    // elements should not be modified manually. They are extended for easier
    // interaction with the Python interface.
    class_<BatStats>(m, "_BatStats");

    class_<Dismissal>(m, "Dismissal")
        .def(init<DismType, Player*, Player*>())
        .def_property_readonly("mode", &Dismissal::get_mode)
        .def_property_readonly("bowler", &Dismissal::get_bowler,
                               return_value_policy::copy)
        .def_property_readonly("fielder", &Dismissal::get_fielder,
                               return_value_policy::copy)
        .def("__str__", &Dismissal::print_dism);

    class_<BatterCard, PlayerCard>(m, "_BatterCard")
        .def(init<Player*>())
        .def_property_readonly("_stats", &BatterCard::get_sim_stats)
        .def_property_readonly("active", &BatterCard::is_active)
        .def_property_readonly("out", &BatterCard::is_out)
        .def_property_readonly("dism", &BatterCard::get_dism,
                               return_value_policy::copy)
        .def("__str__", &BatterCard::print_card);

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