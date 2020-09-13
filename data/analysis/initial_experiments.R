
pacman::p_load(tidyverse, tidymodels, janitor)

bbb <- read_csv('../delivery/bbb_full.csv', na = c("", "-")) %>% as_tibble()

# Prepare data
bbb <- bbb %>% clean_names()
bbb <- bbb %>% mutate_if(is.character, as.factor) %>%
  mutate_at(c("innings", "bat_position"), as.factor)

# Convert bowler overs to balls bowled


# EDA
skimr::skim(bbb)


# Number of observations
obs_count <- bbb %>% group_by(outcome) %>% tally()


wkt <- bbb %>% mutate(is_wkt = as.factor(ifelse(grepl('^W_', outcome), "W", "no"))) %>%
  select(-c(bat_team, bowl_team, bowler, batter, spell_balls, spell_runs, spell_wkts, outcome, venue, toss_win, toss_elect, winner, margin))

# Split
wkt_split <- initial_split(wkt, strata = is_wkt)
wkt_train <- training(wkt_split)
wkt_test <- testing(wkt_split)




# Create Workflow
wkt_recipe <- recipe(is_wkt ~ ., data = wkt_train) %>%
  step_dummy(c(innings, bat_position, bat_arm, bowl_type, host_country)) %>%
  step_interact(terms = ~starts_with("bowl_type"):starts_with("host_country"))
wkt_recipe %>% prep() %>% juice()

wkt_model <- logistic_reg() %>% set_engine("glm")


wkt_wf <- workflow() %>% 
  add_recipe(wkt_recipe) %>% 
  add_model(wkt_model)

# Fit logistic regression
wkt_fit <- fit(wkt_wf, wkt_train)
wkt_fit %>% tidy()

# Compare to test
wkt_test %>% 
  add_column(
    predict(wkt_fit, new_data = wkt_test, type = "prob")
  ) %>% 
  roc_auc(truth = is_wkt, .pred_W, event_level = "second")
