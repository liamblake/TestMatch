pacman::p_load(tidyverse)

# Load BBB
bbb <- readRDS("bbb_full.RDS")

# Remove unwanted factors
bbb <- bbb %>% select(-c(bat_team, bowl_team, batter, bowler, toss_win, venue, winner, dism_mode, is_wkt))

# Split into training, testing
bbb_split <- initial_split(bbb, strata = outcome)
bbb_train <- training(bbb_split)
bbb_test <- testing(bbb_split)

# Save as .csv
save_to_csv <- function(obj, filename) {
  # Save labels
  obj %>% select(outcome) %>% 
    
  # Save predictors
    
}