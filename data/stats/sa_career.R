
pacman::p_load(
  tidyverse, tidymodels
)

stats <- read.csv('C:/users/liaml/Dropbox/Projects/TestMatch/data/stats/stats_mtest.csv')

# Remove unused variables
stats <- as_tibble(stats)
stats <- select(stats, -c("fullName", "scoreName", "team"))

stats <- stats %>% mutate_at(c("team", "batHand", "bowlType"), as.factor)
stats <- stats %>% mutate_at(c("innings", "batAvg", "batSR", "careerBalls", "bowlAvg", "bowlEcon", "bowlSR"), as.numeric)

stats <- stats %>% janitor::clean_names()

skimr::skim(stats)

recipe_stats <- recipe(bowl_avg ~ bowl_econ + bowl_sr + bowl_type, data = stats)
recipe_stats <- recipe_stats %>% step_naomit(bowl_econ, bowl_sr, bowl_type, bowl_avg)
recipe_stats <- recipe_stats %>% step_dummy(all_nominal())


recipe_stats <- recipe_stats %>% step_BoxCox(all_numeric())

recipe_stats <- recipe_stats %>% step_center(all_numeric())
recipe_stats <- recipe_stats %>% step_scale(all_numeric())

recipe_stats <- recipe_stats %>% prep(data = stats)
prep_dat <- recipe_stats %>% juice()

prep_dat %>% ggplot(aes(bowl_avg, bowl_sr)) + geom_point()
prep_dat %>% ggplot(aes(bowl_avg, bowl_econ)) + geom_point()
