"""

"""

from pandas import DataFrame, read_csv
from scrape_match import scrape_ballbyball

# Import
print("Loading match_list.csv")
matches = read_csv('match_list.csv').sample(frac = 1)
print("Succesfully loaded .csv file")


no_succ = 0
for ind in matches.index:

	row = matches.loc[ind]
	print("Scraping %s v %s, %s" % (row['Team1'], row['Team2'], row['StartDate']))

	# Load player csv file
	try:
		filename = 'players/' + row['Team1'] + row['Team2'] + row['StartDate'].replace(' ', '') + '.csv'
		players = read_csv(filename)
	except FileNotFoundError:
		print('Unable to load player CSV file.')
		continue
		
	try:
		scrape_ballbyball(row, players)
		no_succ += 1
	except (AttributeError, IndexError, ValueError) as e:
		print("Scrape failed")
		print(e)


print("====== Scraping Finished ======")
print("Successfully scraped %i matches " % no_succ)
print("out of %i possible" % len(matches.index))
print("===============================")