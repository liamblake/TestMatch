# scrape_players.py
#
# Written by Liam Blake, 07/2020
#
# Scrapes current statistics for each player who has played at least one test match
# since Janurary 1, 2001. This is scraped from ESPNCricInfo and used in the TestMatch
# project.
#


from os import path

from requests import get
from bs4 import BeautifulSoup, SoupStrainer
from pandas import DataFrame, Series
from numpy import floor


def get_profile_data(url):
    page = get(url)
    strainer = SoupStrainer('p', class_='ciPlayerinformationtxt')
    soup = BeautifulSoup(page.content, 'html.parser', parse_only=strainer)

    search = soup.find_all(class_='ciPlayerinformationtxt')

    name = search[0].text.split('Full name\n')[1]

    # Account for entries after batting hand and bowl type
    i = len(search)
    bType = '-'
    while (i > 0):
        try:
            bType = search[i].text.split('Bowling style ')[1]
            break
        except IndexError:
            i = i - 1

    if i == 0:
        i = len(search)
    else:
        i = i - 1

    hand = '-'
    while (i > 0):
        try:
            hand = search[i].text.split('Batting style ')[1]
            break
        except IndexError:
            i = i - 1

    return name, hand, bType


# Global variables
# Directory for saving data
DIR = path.dirname(path.realpath(__file__))
FILENAME = 'PlayerStats.csv'

# Columns of data
COLS = ['fullName', 'scoreName', 'team', 'innings', 'batAvg', 'batSR',
        'careerBalls', 'bowlAvg', 'bowlEcon', 'bowlSR', 'batHand', 'bowlType']


# Start scraping process
print('Starting scraping procedure...')

for p in range(1, 6):
    print('Scraping page ' + str(p) ' of 5...')

    df = DataFrame(columns=COLS)
    i = 0

    # Batting stats
    url = 'https://stats.espncricinfo.com/ci/engine/stats/index.html?class=1;orderby=player;page=' + str(p) + ';size=200;spanmax1=31+Dec+2100;spanmin1=01+Jan+2001;spanval1=span;template=results;type=batting'
    page = get(url)
    strainer = SoupStrainer('tr')
    bat_soup = BeautifulSoup(page.content, 'html.parser', parse_only=strainer)

    # Bowling stats
    url = 'https://stats.espncricinfo.com/ci/engine/stats/index.html?class=1;orderby=player;page=' + str(p) + ';size=200;spanmax1=31+Dec+2100;spanmin1=01+Jan+2001;spanval1=span;template=results;type=bowling'
    page = get(url)
    strainer = SoupStrainer('tr')
    bowl_soup = BeautifulSoup(page.content, 'html.parser', parse_only=strainer)

    for (bat, bowl) in zip(bat_soup.find_all('tr', class_='data1'), bowl_soup.find_all('tr', class_='data1')):
        try:
            profile_url = bat.find('a', class_='data-link')['href']
            name, hand, bType = get_profile_data('https://espncricinfo.com' + profile_url)

            data = [name]

            # Batting stats
            tags_bat = bat.find_all('td')

            sname_team = tags_bat[0].text.split('(')
            data.append(sname_team[0][:-1])
            data.append(sname_team[1][:-1])
            data.append(tags_bat[3].text)
            data.append(tags_bat[7].text)
            data.append(tags_bat[9].text)

            # Bowling stats
            tags_bowl = bowl.find_all('td')
            overs = tags_bowl[4].text
            if overs == '-':
                for i in range(4):
                    data.append('-')
            else:
                overs = float(overs)
                balls = 6*floor(overs) + 10*(overs - floor(overs))
                data.append(balls)
                data.append(tags_bowl[10].text)
                data.append(tags_bowl[11].text)
                data.append(tags_bowl[12].text)

            data = data + [hand, bType]
            df.loc[i] = data
            i = i + 1

            # For testing
            # if i == 10:
            #    break

        except (ValueError, IndexError, AttributeError, TypeError, NameError):
            # Ignore and move on
            pass

    # print(df)
    print('Appending to ' FILENAME)
    df.to_csv(DIR + '/' + FILENAME, index_label=False, mode='a')

print('Scraping complete.')
# NOTE: Connection failure exception is requests.exceptions.ConnectionError
