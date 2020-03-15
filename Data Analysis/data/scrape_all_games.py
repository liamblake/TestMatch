
from pandas import DataFrame, read_csv
from scrape_match import scrape_full_match

# Import
print("Loading match_list.csv")
matches = read_csv('match_list.csv')
print("Succesfully loaded .csv file")

no_succ = 0
for ind in matches.index:

	row = matches.loc[ind]
	
	if row['Country'] == 'ENG' and row['StartDate'] == '4 Aug 2005':


		print("Scraping %s v %s, %s" % (row['Team1'], row['Team2'], row['StartDate']))
		
		#try:
		scrape_full_match(row)
		no_succ += 1
		#except (AttributeError, IndexError, ValueError) as e:
		#	print("Scrape failed")
		#	print(e)


print("====== Scraping Finished ======")
print("Successfully scraped %i matches " % no_succ)
print("out of %i possible" % len(matches.index))
print("===============================")