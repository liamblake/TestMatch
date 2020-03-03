"""
Scrapes from ESPNCricinfo Statsguru data, teams, venue, country and id for
every test match since Januray 1, 2001. The data is saved as csv files:
- match_list.csv: data for each test match, and
- venues.csv: a list of venues and their corresponding countries.

NOTE: Assumes that each team has played less than 200 games since 2001.

"""

from os import path
from requests import get
from bs4 import BeautifulSoup
from pandas import DataFrame

# Directory for saving data
DIR = path.dirname(path.realpath(__file__))

# This list *MUST* be the same order as the country date of first match
COUNTRIES = {1: 'England', 2: 'Australia', 3: 'South Africa', \
             4: 'West Indies', 5: 'New Zealand', 6: 'India', \
             7: 'Pakistan', 8: 'Sri Lanka', 9: 'Zimbabwe', \
             25: 'Bangladesh', 27: 'United Arab Emirates', 29: 'Ireland'}

COUNTRY_CODES = {'Afghanistan': 'AFG', \
                 'Australia': 'AUS', \
                 'Bangladesh': 'BAN', \
                 'England': 'ENG', \
                 'India': 'IND', \
                 'Ireland': 'IRE', \
                 'New Zealand': 'NZL', \
                 'Pakistan': 'PAK', \
                 'South Africa': 'RSA', \
                 'Sri Lanka': 'SRL', \
                 'West Indies': 'WIN', \
                 'Zimbabwe': 'ZIM', \
                 'United Arab Emirates': 'UAE', \
                 'ICC World XI': 'ICC'}


# URL components
URL_START = 'https://stats.espncricinfo.com/ci/engine/stats/index.html?class=1;\
                 filter=advanced;host='
URL_END = ';orderby=start;size=200;spanmin1=01+Jan+2001;spanval1=span;template=\
               results;type=aggregate;view=results'

# Data to extract from each match
COLUMNS = ['urlEnd', 'Team1', 'Team2', 'Venue', 'Country', 'StartDate']

# Storage of data, to output to csv
data = DataFrame(columns=COLUMNS)
venues = {}

for i, c in COUNTRIES.items():
    print("Scraping matches in", c)

    # Construct URL
    url = URL_START + str(i) + URL_END

    # Get HTML and parse to BeautifulSoup
    page = get(url)
    soup = BeautifulSoup(page.content, 'html.parser')

    # Each entry is a "Data1" class
    for j, tr in enumerate(soup.find_all('tr', class_='data1')):

        # New dataframe to append to full dataset
        n_row = DataFrame(index=[0], columns=COLUMNS)
        n_row['Country'] = COUNTRY_CODES[c]


        # Get teams
        teams_str = tr.find_all('td', class_='left')[3]
        teams = teams_str.text.split(' v ')

        n_row['Team1'] = COUNTRY_CODES[teams[0]]
        n_row['Team2'] = COUNTRY_CODES[teams[1]]


        # Get ground and add to dictionary if not already there
        ground = tr.find_all('td', class_='left')[4].text
        if ground not in venues.keys():
            venues.update({ground : COUNTRY_CODES[c]})

        n_row['Venue'] = ground


        # Get start date
        start_date = tr.find_all('td')[6]
        n_row['StartDate'] = start_date.text


        # Get corresponding popup for link
        popup = soup.find('div', class_='engine-dd', id='engine-dd' + str(j + 1))

        # Get href
        href = popup.find_all('a')[1]
        n_row['urlEnd'] = href['href'].split('/')[-1][:-5]

        data = data.append(n_row, ignore_index=True)


# Output data to csv
print('Saving data to match_list.csv')
save_path = path.join(DIR, 'match_list.csv')
data.to_csv(save_path, index=False)

# Output venues to csv
print('Saving venues list to venues.csv')
save_path = path.join(DIR, 'venues.csv')
with open(save_path, 'w') as f:
    for key, val in venues.items():
        f.write("%s,%s\n" % (key, val))
