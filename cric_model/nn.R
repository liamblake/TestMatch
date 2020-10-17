pacman::p_load(tidyverse, tidymodels, vip, corrplot)

# Load data
bbb <- readRDS('bbb_wkt.rds')


# Remove unusued predictors
bbb <- bbb %>% select(-c(start_date, dism_mode, pitch_factor, venue, bowl_team))


# Split data
bbb_split <- initial_split(bbb, strata = is_wkt)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)

# Create recipe
bbb_recipe <- recipe(is_wkt ~ ., data = bbb_train) %>%
  #step_rm(c(bowl_balls, bowl_wkts, career_bat_balls, career_bowl_balls, bowl_avg, bat_arm, bowl_type, team_lead, bowl_runs, bat_position, host_country)) %>%
  step_naomit(all_outcomes()) %>%
  step_center(all_numeric()) %>%
  step_meanimpute(c(bat_avg, bat_sr, bowl_sr)) %>%
  step_scale(all_numeric()) %>%
  step_BoxCox(all_numeric()) %>%
  step_dummy(all_nominal(), -all_outcomes()) %>%
  prep()

# Workflow
bbb_wf<- workflow() %>%
  add_recipe(bbb_recipe) %>%
  add_model(
    mlp(mode = "classification", epochs = 100, hidden_units = 5, dropout = 0.1, activation = "softmax") %>%
      set_engine("keras", verbose = 0)
  )

bbb_fit <- bbb_wf %>% fit(data = bbb_train)
bbb_fit

bbb_val <- bake(bbb_recipe, bbb_test)
val_results <- 
  bbb_test %>%
  bind_cols(
    predict(bbb_fit %>% pull_workflow_fit(), new_data = (sapply(bbb_val %>% select(-is_wkt), as.numeric)))
  )

