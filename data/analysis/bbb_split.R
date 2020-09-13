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

# Add wicket indicator column
bbb <- bbb %>% mutate(is_wkt = as.factor(ifelse(grepl('^W_', outcome), "W", "no")))

# Omit unused columns
bbb <- bbb %>% select(-c(spell_balls, spell_runs, spell_wkts))

# Shuffle data
bbb <- sample_frac(bbb, 1L)

# Split
bbb_split <- initial_split(bbb, strata = outcome)
train <- training(bbb_split)
test <- testing(bbb_split)

# Output to .csv files
saveRDS(bbb, "bbb_full_cleaned.RDS")
saveRDS(train, "bbb_train.RDS")
saveRDS(test, "bbb_test.RDS")
