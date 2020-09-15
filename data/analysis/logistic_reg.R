pacman::p_load(tidyverse, tidymodels, vip, discrim, glmnet)

# Load data
bbb <- readRDS('bbb_full_cleaned.rds')

# Create pitch factor column
bbb <- bbb %>% mutate(pitch_factor = (bat_team_total_runs + bowl_team_total_runs)/(bat_team_total_wkts + bowl_team_total_wkts))

# Remove unusued predictors
bbb <- bbb %>% select(-c(bat_team, bowl_team, batter, bowler, venue, toss_win, winner, margin, bat_win_toss, bat_team_total_runs, bat_team_total_wkts, bowl_team_total_runs, bowl_team_total_wkts, innings, bat_position))

# Simplify problem
bbb <- bbb %>% select(-c(outcome))

# Split data
bbb_split <- initial_split(bbb, strata = is_wkt)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)

# Create recipe
bbb_recipe <- recipe(is_wkt ~ ., data = bbb_train) %>%
  step_normalize(pitch_factor) %>%
  step_BoxCox(all_numeric()) %>%
  step_dummy(all_nominal(), -all_outcomes()) %>%
  step_meanimpute(c(bat_avg, bowl_avg, bat_sr, bowl_sr)) %>%
  step_naomit(all_predictors())
  #step_interact(terms = ~starts_with("host_"):starts_with("bowl_type_"))

prepped <- bbb_recipe %>% prep() %>% juice()


# Best model fitting
# prepped <- prepped %>% relocate(is_wkt, .after = last_col())
# doParallel::registerDoParallel()
# fit <- glmnet(as.data.frame(prepped[,1:41]), as.data.frame(prepped[,42]), family = "binomial")

# Workflow
bbb_wf_logistic <- workflow() %>%
  add_recipe(bbb_recipe) %>%
  add_model(logistic_reg(mode = "classification") %>% set_engine("glm"))

bbb_fit_logistic <- bbb_wf_logistic %>% fit(data = bbb_train)
p <- bbb_fit_logistic %>% pull_workflow_fit()%>% vi() %>% 
  ggplot(aes(Importance, fct_reorder(Variable, Importance), fill = Sign)) + 
  geom_col() + 
  labs(y = NULL)
plotly::ggplotly(p)

View(tidy(bbb_fit_logistic) %>% arrange(p.value))


# Fit on test data
bbb_test %>% 
  add_column(
    predict(bbb_fit_logistic, new_data = bbb_test, type = "prob")
  ) %>% 
  roc_auc(truth = is_wkt, .pred_W, event_level = "second")


# Refit reduced model
# Create recipe
bbb_train_red <- bbb_train %>% select(-c(bowl_wkts, toss_elect, bowl_balls, career_bat_balls))
bbb_recipe_red <- recipe(is_wkt ~ ., data = bbb_train_red) %>%
  step_normalize(pitch_factor) %>%
  step_BoxCox(all_numeric()) %>%
  step_dummy(all_nominal(), -all_outcomes()) %>%
  step_meanimpute(c(bat_avg, bowl_avg, bat_sr, bowl_sr)) %>%
  step_naomit(all_predictors())

# Workflow
bbb_wf_red <- workflow() %>%
  add_recipe(bbb_recipe_red) %>%
  add_model(logistic_reg(mode = "classification") %>% set_engine("glm"))

bbb_fit_red <- bbb_wf_red %>% fit(data = bbb_train_red)
p <- bbb_fit_red %>% pull_workflow_fit()%>% vi() %>% 
  ggplot(aes(Importance, fct_reorder(Variable, Importance), fill = Sign)) + 
  geom_col() + 
  labs(y = NULL)
plotly::ggplotly(p)

# 
# # LDA
# bbb_wf_lda <- workflow() %>% 
#   add_recipe(bbb_recipe) %>%
#   add_model(discrim_linear() %>% set_engine("MASS"))
# 
# bbb_fit_lda <- bbb_wf_lda %>% fit(data = bbb_train)  
# 
# 
