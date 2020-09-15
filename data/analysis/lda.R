pacman::p_load(tidyverse, tidymodels)


# Load data
bbb <- readRDS('bbb_full_cleaned.rds')

# Remove unusued predictors
bbb <- bbb %>% select(-c(bat_team, bowl_team, batter, bowler, venue, toss_win, winner, margin, bat_win_toss))

# Simplify problem
bbb <- bbb %>% select(-c(outcome, bowl_type))

# Split data
bbb_split <- initial_split(bbb, strata = is_wkt)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)

# Create recipe
bbb_recipe <- recipe(is_wkt ~ ., data = bbb_train) %>%
  step_BoxCox(all_numeric()) %>%
  step_dummy(all_nominal(), -all_outcomes()) %>%
  step_interact(terms = ~starts_with("host_"):starts_with("bowl_class_"))

bbb_recipe %>% prep() %>% juice()

tidy(bbb_recipe, n = 1)
