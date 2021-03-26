// -*- lsst-c++ -*-
/* Cards.h
 *
 *
 */

#ifndef CARDS_H
#define CARDS_H

#include <random>
#include <string>

#include "Player.h"

// Global Parameters
const double PACE_MEAN_FATIGUE = 0.1;
const double SPIN_MEAN_FATIGUE = 0.04;

/**
 * @brief Storage for batting statistics for simulation
 *
 *
 */
struct BatStats {
  // Career averages
  double bat_avg;
  double strike_rate;

  // Batting hand
  // false: right, true: left
  bool bat_hand;

  // Current innings
  int runs;
  int balls;
  int fours;
  int sixes;
};

/**
 * @brief Storage for bowling statistics for simulation
 *
 *
 */
struct BowlStats {
  // Career averages
  double bowl_avg;
  double strike_rate;

  // Bowling type
  // 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10:
  // slo, 11: slu
  int bowl_type;

  // Current innings
  int balls;
  int overs;
  int over_balls;
  int maidens;
  int runs;
  int wickets;
  int legal_balls;

  int spell_balls;
  double spell_overs;
  int spell_maidens;
  int spell_runs;
  int spell_wickets;
};

/**
 * @brief Storage of dismissal details
 */
class Dismissal {
 private:
  // Mode of dismissal:
  // 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
  int mode;
  Player* bowler;
  Player* fielder;

  // if bowled or lbw, set fielder = NULL

 public:
  /**
   * @brief
   * @param c_mode
   * @param c_bowler
   * @param c_fielder
   */
  Dismissal(int c_mode, Player* c_bowler = nullptr,
            Player* c_fielder = nullptr);

  /**
   * @brief
   * @return
   */
  std::string print_dism();

  /**
   * @brief
   * @return
   */
  int get_mode();

  /**
   * @brief
   * @return
   */
  Player* get_bowler();

  /**
   * @brief
   * @return
   */
  Player* get_fielder();
};

/**
 * @brief Measure of tiredness of bowler, model for determining next bowler
 *
 *
 */
class Fatigue {
 private:
  double value;

  // Normal distribution object for generating values
  static std::random_device RD;
  static std::mt19937 GEN;
  std::normal_distribution<double>* dist;

  // Parameters
  static double MEAN_PACE_FATIGUE;
  static double MEAN_SPIN_FATIGUE;
  static double EXTRA_PACE_PENALTY;
  static double VAR_PACE_FATIGUE;
  static double VAR_SPIN_FATIGUE;

 public:
  // Constructor
  Fatigue(int c_bowl_type);

  // Getter
  double get_value();

  // Events which change fatigue
  void ball_bowled();
  void wicket();
  void rest(double time);

  // Destructor
  ~Fatigue();
};

/**
 * @brief Abstract base class for bowler and batter cards.
 */
class PlayerCard {

 protected:
  Player* player;

 public:
  // Constructor
  PlayerCard(Player* c_player);

  // Getter
  Player* get_player_ptr();

  // Pure virtual methods
  virtual void update_score(std::string outcome) = 0;
  virtual std::string print_card(void) = 0;

  // Default destructor
};

/**
 * @brief
 */
class BatterCard : public PlayerCard {
  // TODO: implement MATCHTIME

 private:
  BatStats stats;
  bool active;
  bool out;
  Dismissal* dism;

  int mins;

  //
  int playstyle_flag = 0;

 public:
  BatterCard(Player* c_player);

  BatStats get_sim_stats(void);

  bool is_active(void);

  void activate(void);
  void update_score(std::string outcome); //, float mins);
  void dismiss(int d_mode, Player* d_bowler = nullptr,
               Player* d_fielder = nullptr);
  std::string print_card(void);
  std::string print_short(void);
  std::string print_dism(void);

  // Copy constructor
  // BatterCard(const BatterCard& bc);

  ~BatterCard();
};

/**
 * @brief Storage as all information relevant to a bowler bowling in an innings
 */
class BowlerCard : public PlayerCard {

 private:
  BowlStats stats;
  bool active;

  // Flag indicating whether bowler is considered "part-time"
  int competency; // 0 - full-time bowler, 1 - part-time bowler, 2 - only bowl
                  // this player when the opposition is 2/700

  // Rudimentary measure of bowler tiredness, improves with each passing over
  Fatigue tiredness;

  // Tracks number of runs in a current over to determine whether that over was
  // a maiden
  bool is_maiden;

  void add_ball();

  // Determine whether a given player is considered a "parttime bowler"
  static int DETERMINE_COMPETENCY(Player* player);

 public:
  BowlerCard(Player* c_player);

  BowlStats get_sim_stats(void);
  void update_score(std::string outcome);
  void start_new_spell();

  // Get fatigue
  double get_tiredness();
  int get_competency();

  // Over passes (from same end) without bowler bowling - reduces fatigue
  void over_rest();

  std::string print_card(void);
  std::string print_spell(void);
};

template <typename T>
PlayerCard** sort_array(PlayerCard** list, int len,
                        T (Player::*sort_val)() const);

BatterCard** create_batting_cards(Team* team);
BowlerCard** create_bowling_cards(Team* team);

//////////////////////////// PRE-GAME MATCH DETAILS ////////////////////////////

/**
 * @brief
 */
struct PitchFactors {
  double seam;
  double spin;
};

/**
 * @brief
 */
struct Venue {
  std::string name;
  std::string city;
  std::string country;

  PitchFactors* pitch_factors;
};

/**
 * @brief Storage for all information describing a single delivery
 *
 * Stores all information describing a single delivery, including pointers to
 * the Player objects storing the bowler and batter, the encoded outcome,
 * whether the delivery was legal (i.e. not a no ball, wide) and a (currently
 * unused) string containing commentary describing the ball. The Ball struct
 * also functions as a node in the linked list implementation of an Over,
 * storing a reference to the next Ball object in the over. This pointer is null
 * by default.
 */
struct Ball {
  Player* bowler;
  Player* batter;

  std::string outcome;
  bool legal;
  std::string commentary;

  // For linked list implementation
  Ball* next = nullptr;

  Ball* get_next() { return next; };
};

/**
 * @brief
 *
 * ... Functions as BOTH a linked list (with Ball objects as nodes), and nodes
 * in a larger linked list managed by the Innings object. Accordingly contains a
 * pointer to the next Over object in the innings, which is null by default.
 */
class Over {
 private:
  int over_num;

  Ball* first;
  Ball* last;

  int num_balls;
  int num_legal_delivs;

  Over* next = nullptr;

 public:
  // Iterators?

  // Constructor
  Over(int c_over_num);

  /**
   * @brief
   * @param p_next
   */
  void set_next(Over* p_next);

  int get_over_num();
  int get_num_balls();
  int get_num_legal_delivs();
  Ball* get_first();
  Ball* get_last();
  Over* get_next();

  /**
   * @brief Add a Ball object to the end of the over
   * @param ball Pointer to the new Ball object
   */
  void add_ball(Ball* ball);

  ~Over();
};

class Extras {
 private:
  unsigned int byes;
  unsigned int legbyes;
  unsigned int noballs;
  unsigned int wides;

 public:
  Extras();

  bool update_score(std::string outcome);
  std::string print();
  int total();
};

struct FOW {

  Player* batter;
  unsigned int wkts;
  unsigned int runs;
  unsigned int overs;
  unsigned int balls;

  std::string print();

  // TODO: implement value checking for 0 <= balls < 6
};

/**
 * @brief
 *
 */
class Partnership {
 private:
  Player* bat1;
  Player* bat2;

  unsigned int runs;

  unsigned int bat1_runs;
  unsigned int bat1_balls;

  unsigned int bat2_runs;
  unsigned int bat2_balls;

  bool not_out;

 public:
  Partnership(Player* c_bat1, Player* c_bat2);

  // Getters
  Player* get_bat1();
  Player* get_bat2();

  unsigned int get_runs();
  unsigned int get_balls();

  bool get_not_out();

  /**
   * @brief
   *
   * @param n_runs
   * @param scorer
   * @param add_ball
   * @return Milestone*
   */
  Milestone* add_runs(unsigned int n_runs, bool scorer, bool add_ball = true);
  void end();
};

//~~~~~~~~~~~~~~ Match End Objects ~~~~~~~~~~~~~~//

/**
 * @brief
 */
class EndMatch {
 protected:
  Team* winner;
  int margin;

 public:
  EndMatch(Team* c_winner, int c_margin);

  /**
   * @brief
   * @return
   */
  virtual std::string print() = 0;

  // Default destructor
};

/**
 * @brief
 */
class EndInningsWin : public EndMatch {
 public:
  EndInningsWin(Team* c_winner, int c_runs);

  std::string print();
};

/**
 * @brief
 */
class EndBowlWin : public EndMatch {
 public:
  EndBowlWin(Team* c_winner, int c_runs);

  std::string print();
};

/**
 * @brief
 */
class EndChaseWin : public EndMatch {
 public:
  EndChaseWin(Team* c_winner, int c_wkts);

  std::string print();
};

/**
 * @brief
 */
class EndDraw : public EndMatch {
 public:
  EndDraw();

  virtual std::string print();
};

/**
 * @brief
 */
class EndTie : public EndDraw {
 public:
  EndTie();

  std::string print();
};

///// CURRENTLY UNDEFINED - FOR TRACKING MILESTONES

class Milestone {
 private:
  Player* player;
  int value;

  /* Pure virtual method - checks if passed value is
     allowed for given milestone type.
  */
  virtual bool is_permitted(int value) = 0;

 protected:
  std::string desc;

 public:
  Milestone(Player* c_player, int c_value);

  // Getters
  Player* get_player();
  std::string get_desc();
  int get_value();

  virtual std::string string() = 0;
};

class BatMilestone : public Milestone {
 private:
  bool is_permitted(int value);

  int runs;
  int balls;
  int fours;
  int sixes;

 public:
  BatMilestone(Player* batter, int c_milestone, int c_runs, int c_balls,
               int c_fours, int c_sixes);

  std::string string();
};

class PartnershipMilestone : public BatMilestone {};

class BowlMilestone : public Milestone {
 private:
  bool is_permitted(int value);

  int runs;
  int overs;
  int balls;
  int maidens;

 public:
  BowlMilestone(Player* bowler, int c_milestone, int c_runs, int c_overs,
                int c_balls, int c_maidens);

  std::string string();
};

#endif // CARDS_H
