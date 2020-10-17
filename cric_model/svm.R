pacman::p_load(tidyverse, tidymodels, vip, corrplot)

# Load data
bbb <- readRDS('bbb_wkt.rds')


# Remove unusued predictors
bbb <- bbb %>% select(-c( innings, start_date, dism_mode, pitch_factor, venue, bowl_team))


# Split data
bbb_split <- initial_split(bbb, strata = is_wkt)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)

# Create recipe
bbb_recipe <- recipe(is_wkt ~ ., data = bbb_train) %>%
  step_rm(c(bowl_balls, bowl_wkts, career_bat_balls, career_bowl_balls, bowl_avg, bat_arm, bowl_type, team_lead, bowl_runs, bat_position, host_country)) %>%
#  step_center(all_numeric()) %>%
#  step_scale(all_numeric()) %>%
#  step_BoxCox(all_numeric()) %>%
  step_dummy(all_nominal(), -all_outcomes()) %>%
  step_meanimpute(c(bat_avg, bat_sr, bowl_sr)) %>%
  step_interact(terms = ~starts_with("bowl_class_"):c(seam_factor, spin_factor))

# Workflow
bbb_wf<- workflow() %>%
  add_recipe(bbb_recipe) %>%
  add_model(svm_poly(mode = "classification") %>% set_engine("kernlab"))

bbb_fit <- bbb_wf %>% fit(data = bbb_train)
p <- bbb_fit %>% pull_workflow_fit()%>% vi() %>% 
  ggplot(aes(Importance, fct_reorder(Variable, Importance), fill = Sign)) + 
  geom_col() + 
  labs(y = NULL)
plotly::ggplotly(p)

View(tidy(bbb_fit_logistic) %>% arrange(p.value))


# Fit on test data
test_fitted <- bbb_test %>% 
  add_column(
    predict(bbb_fit, new_data = bbb_test, type = "prob")
  ) 

# ROC Curve
test_fitted %>% 
  roc_curve(truth = is_wkt, .pred_W, event_level = "second")%>% 
  add_column(id = "test") %>% 
  ggplot(aes(1 - specificity, sensitivity, col = id)) + geom_path()


train_fitted <- bbb_train %>% 
  add_column(
    predict(bbb_fit, new_data = bbb_train, type = "prob")
  ) 
