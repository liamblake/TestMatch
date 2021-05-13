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

/**
 * @brief Represents the possible results of a match. Note that string
 * representations of this enumeration are handled by the MatchResult
 * object.
 *
 */
enum ResultType {
    draw,        /*!< Drawn match. */
    win_chasing, /*!< Win by batting team in fourth innings, i.e. the
                    batting team have successfully reached the target. */
    win_bowling, /*!< Win by bowling team in the fourth innings, i.e. the
                    batting team have been bowled out before reaching the
                    target. */
    win_innings, /*!< Win by an innings, i.e. the batting team have been
                    bowled out in the third innings while still trailing. */
    tie /*!< Tied match, i.e. the batting team has been bowled out in the
           fourth innings with the scores level. */
};

enum TossChoice {
    bat,   /*!< Elected to bat. String representation of "bat". */
    field, /*!< Elected to bowl/field. String representation of "bowl" */
};

// Conversions to and from boolean and string representations
std::string str(Arm arm);
char chr(Arm arm);

std::string str(BowlType bowltype);
std::string long_str(Arm arm, BowlType bowltype);

std::string str(DismType dismtype);

#endif // ENUMS_H