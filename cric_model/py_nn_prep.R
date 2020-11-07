pacman::p_load(tidyverse, tidymodels)

# Load BBB
bbb <- readRDS("bbb_full.RDS")

# Remove unwanted factors
bbb <- bbb %>% select(-c(bat_team, bowl_team, batter, bowler, toss_win, venue, winner, dism_mode, is_wkt, bowl_class, margin)) %>%
  mutate(outcome = case_when(
    str_detect(outcome, "W_") ~ "W", 
    TRUE ~ outcome))




# Encode categorical variables
rc <- recipe(outcome ~ ., data = bbb) %>% step_naomit(outcome) %>% step_dummy(all_nominal()) %>% step_meanimpute(all_numeric())
bbb_pp <- rc %>% prep(data = bbb) %>% juice()

bbb_pp <- bbb_pp %>% add_column(outcome_X0 = as.integer(!rowSums((bbb_pp %>% select(starts_with("outcome")))[1:26])))

# Add dot ball column


# Split into training, testing
bbb_split <- initial_split(bbb_pp)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)


# Save as .csv
save_to_csv <- function(obj, filename) {
  # Save labels
  obj %>% select(starts_with("outcome")) %>% write.csv(paste(filename, '_labs.csv', sep = ""), row.names = FALSE)
    
  # Save predictors
  obj %>% select(!starts_with("outcome")) %>% write.csv(paste(filename, '_preds.csv', sep = ""), row.names = FALSE)
}

save_to_csv(bbb_train, "data/bbb_train")
save_to_csv(bbb_test, "data/bbb_test")
