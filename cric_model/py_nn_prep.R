pacman::p_load(tidyverse, tidymodels)

set.seed(8112020)

# Save as .csv
save_to_csv <- function(obj, filename) {
  # Save labels
  obj %>% select(starts_with("outcome")) %>% write.csv(paste(filename, '_labs.csv', sep = ""), row.names = FALSE)
  
  # Save predictors
  obj %>% select(!starts_with("outcome")) %>% write.csv(paste(filename, '_preds.csv', sep = ""), row.names = FALSE)
}

# Encode categorical variables and
prep_data <- function(df, filename, no_outs, add_class = "") {
  # Encode categorical variables
  rc <- recipe(outcome ~ ., data = df) %>% 
    step_naomit(outcome) %>%
    step_dummy(all_nominal()) %>% 
    step_meanimpute(all_numeric())
    
  df_pp <- rc %>% prep(data = df) %>% juice()
  
  # Account for reference category
  if (no_outs > 2) {
    df_pp <- df_pp %>% add_column(nc = as.integer(!rowSums((df_pp %>% select(starts_with("outcome")))[1:(no_outs - 1)])))
    ncn <- paste("outcome_X", add_class, sep = "") 
    df_pp <- rename(df_pp, !!ncn := nc)
  }
  
  # Split into training, testing
  df_split <- initial_split(df_pp)
  df_train <- training(df_split)
  df_test <- testing(df_split)
  
  # Export to .csv
  save_to_csv(df_train, paste("data/", filename, "_train", sep = ""))
  save_to_csv(df_test, paste("data/", filename, "_test", sep = ""))
}

# Load BBB
bbb <- readRDS("bbb_full.RDS")

# Remove unwanted factors
bbb <- bbb %>% select(-c(bat_team, bowl_team, batter, bowler, toss_win, venue, winner, bowl_class, margin)) %>%
  mutate(outcome = case_when(
    str_detect(outcome, "W_") ~ "W", 
    TRUE ~ outcome))

# Remove outcomes which occur too infrequently
bbb$outcome <- fct_lump_min(bbb$outcome, 15)
bbb <- bbb[bbb$outcome != "Other",]
bbb$outcome <- droplevels(bbb$outcome)

# Add extras column
bbb <- bbb %>% mutate(runs = case_when(
  str_detect(outcome, "W") ~ 0, 
  TRUE ~ as.double(substring(outcome, 1, 1))
)) %>% 
  mutate(extras = as.factor(case_when(
    nchar(as.character(outcome)) > 1 ~ substring(outcome, 2),
    TRUE ~ "off_bat"
  )))

# Factors
bbb <- bbb %>% mutate_at(c("innings", "bat_position", "team_wkts", "bowl_wkts"), as.factor) %>% mutate_if(is.character, as.factor)

# EDA - informs preprocessing
bbb %>% ggplot(aes(match_balls)) + geom_histogram(binwith = 0.5, fill = "maroon", colour = "black")
bbb %>% ggplot(aes(inn_balls)) + geom_histogram(binwith = 0.5, fill = "maroon", colour = "black")
bbb %>% ggplot(aes(match_balls)) + geom_histogram(binwith = 0.5, fill = "maroon", colour = "black")



# Save full data
prep_data(bbb %>% select(-c(is_wkt, dism_mode, extras)), "bbb_full", 22, "0")

# Wicket data
bbb %>% select(-c(outcome, dism_mode, extras)) %>%
  rename(outcome = is_wkt) %>%
  na.omit(outcome) %>%
  prep_data("is_wkt", 2)


# Dismissal data
bbb %>% select(-c(outcome, is_wkt, extras)) %>%
  rename(outcome = dism_mode) %>%
  na.omit(outcome) %>%
  prep_data("dism_mode", 8, "bowled")


# Ball outcome data
bbb %>% filter(outcome != "W") %>% 
  select(-c(outcome, is_wkt, dism_mode, runs)) %>%
  rename(outcome = extras) %>%
  na.omit(outcome) %>%
  prep_data("outcome", 5, "b")

# Runs scored for each ball outcome
bbb %>% filter(outcome != "W" & extras == "off_bat") %>% 
  select(-c(outcome, is_wkt, dism_mode, extras)) %>%
  rename(outcome = runs) %>%
  na.omit(outcome) %>%
  prep_data("runs", 1)

bbb %>% filter(extras == "b") %>% 
  select(-c(outcome, is_wkt, dism_mode, extras)) %>%
  rename(outcome = runs) %>%
  na.omit(outcome) %>%
  prep_data("byes", 1)

bbb %>% filter(extras == "lb") %>% 
  select(-c(outcome, is_wkt, dism_mode, extras)) %>%
  rename(outcome = runs) %>%
  na.omit(outcome) %>%
  prep_data("legbyes", 1)

bbb %>% filter(extras == "nb") %>% 
  select(-c(outcome, is_wkt, dism_mode, extras)) %>%
  rename(outcome = runs) %>%
  na.omit(outcome) %>%
  prep_data("noballs", 1)

bbb %>% filter(extras == "wd") %>% 
  select(-c(outcome, is_wkt, dism_mode, extras)) %>%
  rename(outcome = runs) %>%
  na.omit(outcome) %>%
  prep_data("wides", 1)