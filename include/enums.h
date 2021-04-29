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
    med,      /*!< Medium paced bowling. String representation of "m". */
    med_fast, /*!< Medium-fast paced bowling. String representation of "mf". */
    fast_med, /*!< Fast-medium paced bowling. String representation of "fm". */
    fast,     /*!< Fast paced bowling. String representation of "f". */
    offbreak, /*!< Offspin bowling. Note that this can refer to either right-arm
                fingerspin or left-arm wristspin. String representation of "ob".
              */
    legbreak  /*!< Legspin bowling. Note that this can refer to either right-arm
                wristspin or left-arm finger. String representation of "lb". */
};

/**
 * @brief Represents the type of dismissal.
 *
 */
enum DismType {
    bowled,  /*!< Bowled. String representation of "b". */
    lbw,     /*!< Leg before wicket. String representation of "lbw". */
    caught,  /*!< Caught by fielder. String representation of "c". */
    c_and_b, /*!< Caught and bowled by bowler. String representation of "c&b".
              */
    run_out, /*!< Run out. String representation of "ro". */
    stumped  /*!< Stumped by wicketkeeper. String representation of "st". */
};

// Conversions to and from boolean and string representations
std::string str(Arm arm);
char chr(Arm arm);

std::string str(BowlType bowltype);
std::string long_str(Arm arm, BowlType bowltype);

std::string str(DismType dismtype);

#endif // ENUMS_H