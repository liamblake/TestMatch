pacman::p_load(tidyverse, tidymodels, vip, corrplot)

# Load data
bbb <- readRDS('bbb_wkt.rds')

# Very complicated and highly tuned model
fast_model <- bbb %>% filter(grepl('f', bowl_type) & is_wkt == "W" ) %>% group_by(dism_mode) %>% summarise (n = n()) %>% mutate(freq = n / sum(n))
spin_model <- bbb %>% filter(!grepl('f', bowl_type) & is_wkt == "W") %>% group_by(dism_mode) %>% summarise (n = n()) %>% mutate(freq = n / sum(n))

fast_model
spin_model

# Not really going for prediction here, rather just a way of simulating the type of dismissal to give reasonable long-term proportions