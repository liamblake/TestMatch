pacman::p_load(tidyverse, tidymodels, janitor)

# Load raw data
bbb <- read_csv('../delivery/bbb_full.csv', na = c("", "-")) %>% as_tibble()

# Prepare data
bbb <- bbb %>% clean_names()
bbb <- bbb %>% mutate_if(is.character, as.factor) %>%
  mutate_at(c("innings", "bat_position", "game_id"), as.factor)

# Convert career overs to balls
bbb <- bbb %>% mutate(career_overs = 5*floor(career_overs) + career_overs) %>%
  rename(career_bat_balls = career_balls, career_bowl_balls = career_overs)

# Create simpler factor columns
bbb <- bbb %>% mutate(is_wkt = as.factor(ifelse(grepl('^W_', outcome), "W", "no")))
bbb <- bbb %>% mutate(bowl_class = as.factor(ifelse(bowl_type %in% c("lc", "lo", "rls", "rob"), "spin", "seam")))
bbb <- bbb %>% mutate(bat_win_toss = as.factor(ifelse(bat_team == toss_win, "yes", "no")))
bbb <- bbb %>% mutate(bat_home_away = as.factor(ifelse(bat_team == host_country, "home", "away")))
bbb <- bbb %>% mutate(dism_mode = as.factor(ifelse(is_wkt == "W", substring(outcome, 3), NA)))

# Pitch factors
g_wkts_sum <- bbb %>% group_by(game_id) %>% 
  filter(is_wkt == "W") %>% 
  tally(bowl_class == "seam") %>%
  add_column(spin_wkts = (
    bbb %>% group_by(game_id) %>% filter(is_wkt == "W" ) %>% tally(bowl_class == "spin")
  )[,2]) %>%
  add_column(total_wkts = (
    bbb %>% group_by(game_id) %>% summarise(mean(bat_team_total_wkts + bowl_team_total_wkts))
  )[,2]) %>%
  rename(seam_wkts = n)

bbb <- bbb %>% mutate(pitch_factor = (bat_team_total_runs + bowl_team_total_runs)/(bat_team_total_wkts + bowl_team_total_wkts)) %>%
  mutate(seam_factor = unlist(pitch_factor*g_wkts_sum[as.integer(game_id),2]/g_wkts_sum[as.integer(game_id),4], use.name = FALSE)) %>%
  mutate(spin_factor = unlist(pitch_factor*g_wkts_sum[as.integer(game_id),3]/g_wkts_sum[as.integer(game_id),4], use.name = FALSE))

# Extras


# Runs scored


# Omit unused columns
bbb <- bbb %>% select(-c(spell_balls, spell_runs, spell_wkts))

# Shuffle data and split 
bbb <- sample_frac(bbb, 1L)

bbb_wkts <- bbb %>% select(-c(bat_team, batter, bowler, outcome, bat_team_total_runs, bat_team_total_wkts, bowl_team_total_wkts, bowl_team_total_runs, toss_win, toss_elect, winner, margin, game_id, bat_win_toss))

# Output to .RDS files
saveRDS(bbb_wkts, "bbb_wkt.RDS")
