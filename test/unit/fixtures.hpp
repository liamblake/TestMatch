/* Test fixtures used across multiple modules and suites.*/

#include "testmatch\pregame.hpp"
#include "testmatch\team.hpp"

struct F_TeamAus {

    F_TeamAus()
        : a1("David", "Warner", "DA",
             {155, 48.94, 72.85, 342, 67.25, 85.5, 4.71, left, left, legbreak}),
          a2("Will", "Pucovski", "WJ",
             {1, 42.54, 60.21, 0, 1000, 1000, 4.00, right, right, med}),
          a3("Marnus", "Labuschagne", "M",
             {23, 63.43, 56.52, 756, 38.66, 63.0, 3.68, right, right,
              legbreak}),
          a4("Steve", "Smith", "SPD",
             {131, 62.84, 55.3, 1381, 56.47, 81.2, 4.17, right, right,
              legbreak}),
          a5("Travis", "Head", "TM",
             {28, 41.96, 50.41, 126, 68.32, 63.7, 3.61, left, right, offbreak}),
          a6("Cameron", "Green", "C",
             {7, 40.71, 40.68, 264, 30.30, 50.7, 2.98, right, right, fast_med}),
          a7("Tim", "Paine", "TD",
             {50, 31.66, 44.24, 0, 1000, 1000, 4.00, right, right, med}),
          a8("Pat", "Cummins", "PJ",
             {44, 17.02, 38.51, 6761, 21.82, 47.2, 2.76, right, right,
              fast_med}),
          a9("Jhye", "Richardson", "JA",
             {1, 12.95, 58.81, 306, 23.74, 52.3, 2.41, right, right, fast_med}),
          a10("Josh", "Hazlewood", "JR",
              {68, 12.02, 45.22, 11887, 25.65, 56.0, 2.74, left, right,
               fast_med}),
          a11("Nathan", "Lyon", "NM",
              {123, 12.27, 46.99, 24568, 31.58, 62.9, 3, right, right,
               offbreak}) {
        aus = {"Australia", &a1, &a2,  &a3,  &a4, &a5, &a6, &a7,
               &a8,         &a9, &a10, &a11, 6,   6,   9,   8};
    };

    Team aus;
    Player a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;
};

struct F_TeamNZ {

    F_TeamNZ()
        : b1("Tom", "Latham", "TWM",
             {92, 42.34, 46.66, 0, 1000, 1000, 4.00, left, left, med}),
          b2("Tom", "Blundell", "TA",
             {11, 47.22, 49.47, 18, 1000, 1000, 4.33, right, right, offbreak}),
          b3("Kane", "Williamson", "KS",
             {140, 50.99, 51.63, 2103, 40.62, 72.5, 3.36, right, right,
              offbreak}),
          b4("Ross", "Taylor", "LRPL",
             {178, 46.1, 60, 96, 24, 48, 3, right, right, offbreak}),
          b5("Henry", "Nicholls", "HM",
             {50, 39.7, 49.39, 0, 1000, 1000, 4.00, left, right, offbreak}),
          b6("BJ", "Watling", "BJ",
             {110, 38.5, 42.35, 0, 1000, 1000, 4.00, right, right, med}),
          b7("Mitchell", "Santner", "MJ",
             {29, 25.55, 42.36, 3746, 44.71, 96, 2.79, left, left, legbreak}),
          b8("Kyle", "Jamieson", "KA",
             {6, 21.47, 55, 1202, 21.14, 42.2, 3, right, right, fast_med}),
          b9("Tim", "Southee", "TG",
             {106, 17.37, 85.84, 16393, 29, 57.7, 3.01, right, right,
              med_fast}),
          b10("Neil", "Wagner", "N",
              {63, 12.5, 44.88, 10743, 26.6, 52.1, 3.06, left, left, med_fast}),
          b11("Trent", "Boult", "TA",
              {82, 15.2, 56.86, 14874, 27.65, 55.7, 2.97, right, left,
               fast_med}) {
        nz = {"New Zealand", &b1, &b2,  &b3,  &b4, &b5, &b6, &b7,
              &b8,           &b9, &b10, &b11, 2,   5,   10,  8};
    }

    Team nz;
    Player b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
};

struct F_Pregame : F_TeamAus, F_TeamNZ {

    F_Pregame() {
        pf = {0.75995148, 0.24004852};
        venue = {"Lords", "London", "ENG", &pf};
        pregame = {&venue, &aus, &nz};
    }

    PitchFactors pf;
    Venue venue;
    Pregame pregame;
};