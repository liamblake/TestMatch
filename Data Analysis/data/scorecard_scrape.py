from scrape_ballbyball import scrape_game

game_list = [('10839', '1062574/india-vs-australia-2nd-test-ind-v-aus-2016-17'),
			 ('19406', '1193500/afghanistan-vs-west-indies-only-test-afghanistan-in-india-2019-20'),
			 ('19430', '1187007/india-vs-south-africa-1st-test-icc-world-test-championship-2019-2021'),
			 ('19297', '1187672/new-zealand-vs-england-2nd-test-england-in-new-zealand-2019-20'),
			 ('19430', '1152846/england-vs-australia-1st-test-icc-world-test-championship-2019-2021'),
			 ('18649', '1144153/south-africa-vs-pakistan-1st-test-pak-in-sa-2018-19'),
			 ('19430', '1187685/new-zealand-vs-india-1st-test-icc-world-test-championship-2019-2021'),
			 ('11534', '742613/new-zealand-vs-pakistan-2nd-test-new-zealand-tour-of-united-arab-emirates-2014-15')]


for g in game_list:
	try:
		print("Scraping", g)
		scrape_game(g[0], g[1])
	except (ValueError, KeyError, AttributeError, NameError, TypeError) as e:
		print("Failed")
		print(e)

