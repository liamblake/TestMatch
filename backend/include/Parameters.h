/*  PARAMETERS.H

    Contains all global parameters required in simulation.
    These can be tweaked (and then the full src recompiled)
    to make modifications to how the simulation runs.
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H


// Session time details
const float START_TIME = 10.30;
const float LUNCH_START = 12.30;
const int LUNCH_DUR = 2400;        // 40 minutes
const float TEA_START = 15.10;
const int TEA_DUR = 1200;          // 20 minutes
const float CLOSE_PLAY = 17.30;

const int OVERCHA_DUR = 30;
const int DRINKS_DUR = 300;        // 5 minutes
const int INNBRE_DUR = 600;        // 10 minutes

// Maximum amount of time which a session can be extended by
const int MAXIMUM_EXTEND = 1800;   // 30 minutes

// Delivery duration statistics
const double PACE_MINDUR = 25;
const double PACE_MAXDUR = 60;
const double SPIN_MINDUR = 15;
const double SPIN_MAXDUR = 40;
const double PACE_MEANDUR = 45;
const double SPIN_MEANDUR = 25;
const double DEL_STDDUR = 0.5;
const double RUN_DUR = 10;
const double BOUND_DUR = 30;




// Fatigue measures - how quickly bowlers tire
const double MAX_FATIGUE = 100;
const double STEP_FATIGUE_FAST = 6;
const double STEP_FATIUE_MED = 3;
const double STEP_FATIGUE_SLOW = 1;
// This model needs some improvement

#endif