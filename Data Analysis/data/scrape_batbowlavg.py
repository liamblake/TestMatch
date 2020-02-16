# -*- coding: utf-8 -*-
"""
Created on Sun Feb 16 11:34:12 2020
"""

from bs4 import BeautifulSoup
from requests import get


# Get pregrame stats 
def get_pregame_avgs(url):

    output = {}
    
    # Get scorecard HTML
    page = get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    all_scorecards = soup.find_all('article', class_ = 'sub-module scorecard')

    players1, names1 = get_players(all_scorecards[0])
    players2, names2 = get_players(all_scorecards[1])
    
    for id in players1 + players2:
        print(id)


    return output


def get_players(inns):
    batters = inns.find_all('div', class_ = 'cell batsmen')
    ids = []
    names = []
    
    for b in batters:
        for r in b.find_all(href=True):
            url = r['href']
            
            # Get ID from url
            ids.append(url.split('/')[-1][:-5])

    
    # Also include DNB
    dnb = inns.find_all('div', class_ = 'wrap dnb')[0]
    for r in dnb.find_all('a', href=True):
        url = r['href']
        
        # Get ID from url
        ids.append(url.split('/')[-1][:-5])
        
    
    return(ids, names)
    
    
get_pregame_avgs('https://www.espncricinfo.com/series/18659/scorecard/1152849/england-vs-australia-4th-test-icc-world-test-championship-2019-2021')