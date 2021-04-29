#ifndef ENUMS_H
#define ENUMS_H

#include <string>

/**
 * @brief Represents the arm used by a player to bat or bowl.
 *
 */
enum Arm { left, right };

/**
 * @brief Represents the bowling type of a player, without the arm.
 *
 */
enum BowlType {
    med,      /*!< Medium paced bowling. */
    med_fast, /*!< Medium-fast paced bowling. */
    fast_med, /*!< Fast-medium paced bowling. */
    fast,     /*!< Fast paced bowling. */
    offbreak, /*!< Offspin bowling. Note that this can refer to either right-arm
                fingerspin or left-arm wristspin. */
    legbreak  /*!< Legspin bowling. Note that this can refer to either right-arm
                wristspin or left-arm finger. */
};

/**
 * @brief Represents the type of dismissal.
 *
 */
enum DismType {
    bowled,  /*!< Bowled. */
    lbw,     /*!< Leg before wicket. */
    caught,  /*!< Caught by fielder. */
    c_and_b, /*!< Caught and bowled by bowler. */
    run_out, /*!< Run out. */
    stumped  /*!< Stumped by wicketkeeper. */
};

// Conversions to and from boolean and string representations
std::string str(Arm arm);
char chr(Arm arm);

std::string str(BowlType bowltype);
std::string long_str(Arm arm, BowlType bowltype);

std::string str(DismType dismtype);

#endif // ENUMS_H