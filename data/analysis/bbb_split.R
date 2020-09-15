pacman::p_load(tidyverse, tidymodels, janitor)

# Load raw data
bbb <- read_csv('../delivery/bbb_full.csv', na = c("", "-")) %>% as_tibble()

# Prepare data
bbb <- bbb %>% clean_names()
bbb <- bbb %>% mutate_if(is.character, as.factor) %>%
  mutate_at(c("innings", "bat_position"), as.factor)

# Convert career overs to balls
bbb <- bbb %>% mutate(career_overs = 5*floor(career_overs) + career_overs) %>%
  rename(career_bat_balls = career_balls, career_bowl_balls = career_overs)

# Create simpler factor columns
bbb <- bbb %>% mutate(is_wkt = as.factor(ifelse(grepl('^W_', outcome), "W", "no")))
bbb <- bbb %>% mutate(bowl_class = as.factor(ifelse(bowl_type %in% c("lc", "lo", "rls", "rob"), "spin", "seam")))
bbb <- bbb %>% mutate(bat_win_toss = as.factor(ifelse(bat_team == toss_win, "yes", "no")))
bbb <- bbb %>% mutate(bat_home_away = as.factor(ifelse(bat_team == host_country, "home", "away")))
bbb <- bbb %>% mutate(dism_mode = as.factor(ifelse(is_wkt == "W", substring(outcome, 3), NA)))

# Omit unused columns
bbb <- bbb %>% select(-c(spell_balls, spell_runs, spell_wkts))

# Shuffle data
bbb <- sample_frac(bbb, 1L)

# Split
bbb_split <- initial_split(bbb, strata = outcome)
train <- training(bbb_split)
test <- testing(bbb_split)

# Output to .RDS files
saveRDS(bbb, "bbb_full_cleaned.RDS")
saveRDS(train, "bbb_train.RDS")
saveRDS(test, "bbb_test.RDS")
