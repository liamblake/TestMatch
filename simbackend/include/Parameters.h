#ifndef PARAMETERS_H
#define PARAMETERS_H


/* Dynamic match time parameters

    All times are encoded as seconds
*/

// Session time details
extern float START_TIME = 10.30;
extern float LUNCH_START = 12.30;
extern int LUNCH_DUR = 2400;        // 40 minutes
extern float TEA_START = 15.10;
extern int TEA_DUR = 1200;          // 20 minutes
extern float CLOSE_PLAY = 17.30;

extern int DRINKS_DUR = 300;        // 5 minutes
extern int INNBRE_DUR = 600;        // 10 minutes

// Maximum amount of time which a session can be extended by
extern int MAXIMUM_EXTEND = 1800;   // 30 minutes

// Delivery duration statistics
extern double PACE_MINDUR = 25;
extern double PACE_MAXDUR = 60;
extern double SPIN_MINDUR = 15;
extern double SPIN_MAXDUR = 40;
extern double PACE_MEANDUR = 45;
extern double SPIN_MEANDUR = 25;
extern double DEL_STDDUR = 0.5;
extern double RUN_DUR = 10;
extern double BOUND_DUR = 30;

extern int OVERCHA_DUR = 30;


#endif