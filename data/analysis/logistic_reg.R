pacman::p_load(tidyverse, tidymodels)

# Load data
bbb_train <- readRDS('bbb_train.rds')
bbb_test <- readRDS('bbb_test.rds')

# Remove unused factors
bbb_train <- bbb_train %>% select(-c(bat_team, bowl_team, bowler, batter, venue, toss_win, toss_elect, winner, margin, is_wkt, bat_position))


# Recipe
bbb_recipe <- recipe(outcome ~ ., data = bbb_train) %>%
  step_naomit(all_predictors()) %>%
  step_naomit(all_outcomes()) %>%
  step_other(outcome, threshold = 0.0001)  %>%
#  step_filter(outcome != "other") %>%
  step_dummy(all_nominal(), -all_outcomes())

bbb_recipe %>% prep() %>% juice()

bbb_model <- multinom_reg(penalty = tune()) %>% 
  set_engine("glmnet") %>% 
  set_mode("classification")


bbb_wf <- workflow() %>% 
  add_recipe(bbb_recipe) %>% 
  add_model(bbb_model)

bbb_cv <- vfold_cv(bbb_train, strata = outcome)

doParallel::registerDoParallel()
bbb_tune <- tune_grid(
  object = bbb_wf,
  resamples = bbb_cv,
  grid = grid_regular(penalty(), levels = 50)
)

bbb_tune %>%
  collect_metrics()


# Fit logistic regression
bbb_fit <- fit(bbb_wf, bbb_train)
bbb_fit %>% tidy()
