/**
 * @file Model.h
 * @author Liam Blake
 * @brief Interface for prediction models as implemented in the library.
 * @version 0.1
 * @date 2021-03-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef PREDICTION_H
#define PREDICTION_H

#include <string>
#include <vector>

#include "Cards.h"
#include "Player.h"

namespace Model {

extern int NUM_DELIV_OUTCOMES;
extern std::vector<std::string> DELIV_OUTCOMES;
extern int NUM_DISM_MODES;
extern std::vector<std::string> DISM_MODES_STATIC;

/**
 * @brief Determine the probability of electing to bat at the toss
 *
 * @param spin_factor The spin factor describing the pitch conditions
 * @return double Probability of electing to bat
 */
double MODEL_TOSS_ELECT(double spin_factor);

/**
 * @brief
 *
 * @param bat
 * @param bowl
 * @param match
 * @return double*
 */
double* MODEL_DELIVERY(BatStats bat, BowlStats bowl);

/**
 * @brief
 *
 * @param bowltype
 * @return int
 */
int MODEL_WICKET_TYPE(int bowltype);

/**
 * @brief Determine the probability of declaring on a given ball.
 *
 * @param lead
 * @param match_balls
 * @param is_wkt
 * @param innings
 * @return double
 */
double MODEL_DECLARATION(int lead, int match_balls, bool is_wkt, int innings);

/**
 * @brief Generate a probability for enforcing the follow-on, using the lead
 *
 * @param lead Lead of bowling team at end of previous innings.
 * @return Probability of enforcing the follow-on
 */
double MODEL_FOLLOW_ON(int lead);

}; // namespace Model

#endif // PREDICTION_H
