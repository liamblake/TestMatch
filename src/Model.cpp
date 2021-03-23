/**
 * @file Model.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-03-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Model.h"
#include "Utility.h"
#include <cmath>

using namespace Model;

/* Somewhat terrible fit to the toss elect probabilities in actual data
 * Note that spin_factor = 1 - seam_factor, so we only need to consider
 * the spin factor when calculating the probability. This is based on the
 * intuition that in extreme spinning conditions, a team will bat first,
 * whereas in extreme seaming conditions, a team will bowl first.
 *
 * Using a probability rather than a hard choice adds in that extra
 *uncertainty that appears whenever human decision is involved.
 *
 * This model, along with the entire pitch condition set-up, will probably
 * be eventually improved.
 **/
double MODEL_TOSS_ELECT(double spin_factor) {
  // Exponential model
  double a = 0.05;
  return a * exp(log(0.9 / a) * spin_factor);
}

/**
 *
 */
double MODEL_DECLARATION(int lead, int match_balls, bool is_wkt, int innings) {
  return 0;
}

/**
 * Current model is a logistic regression on the lead. The lead is first
 * transformed with a Box-Cox transformation, then used to calculate the
 * probability. The model was fitted on historical data using R.
 *
 * The model is
 * \f[
 *  p = \frac{1}{1 + \exp{-1101.903 + 1058.466 \times\text{t_lead}}}.
 * \f]
 */
double MODEL_FOLLOW_ON(int lead) {
  // Logistic regression, fitted in R

  // Preprocessing of lead value
  double t_lead = boxcox(lead, -0.9561039); // Box-Cox transform

  // Fitted model
  double logit = -1101.903 + 1058.466 * t_lead;
  return 1 / (1 + exp(logit));
}