# -*- coding: utf-8 -*-
"""
Created on Sat Jan 25 11:28:06 2020



Assumptions
    - At least three innings in match    
    - No more than 10 extras on any one legal delivery
    - No stumpings off wides


Each of these need to be addressed


"""


import pandas as pd
from bs4 import BeautifulSoup
from os import path
from requests import get


# Global variables
DIR = path.dirname(path.realpath(__file__))
NAMES = {'Afghanistan': 'AFG', \
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
         'Zimbabwe': 'ZIM'}
NUM_MONTHS = {'Jan': '01', \
              'Feb': '02', \
              'Mar': '03', \
              'Apr': '04', \
              'May': '05', \
              'Jun': '06', \
              'Jul': '07', \
              'Aug': '08', \
              'Sep': '09', \
              'Oct': '10', \
              'Nov': '11', \
              'Dec': '12'}
DATA_COLS = ['outcome', 'innings', 'team_wkts', 'team_score', 
                                   'team_lead', 'bat_score', 'bat_balls', 'bat_avg', 
                                   'bowl_balls', 'bowl_runs', 'bowl_wkts', 'bowl_avg']


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
    

# Extracts bowler name and batter name from delivery description. Pass delivery
# as string 
def desc_to_name(desc_txt):
    split = desc_txt.split(' ')
    
    bowl = split[0]
    bat = split[2][:-1]
    
    # Ensure no '\n' at end of bowler
    if bowl[-1:] == "\n":
        bowl = bowl[:-1]
    
    return bowl, bat


def data_row(outcome, desc, pregame_avgs, innings):
    # Globals
    global bats
    global bowls
    global team_wkts
    global team_score
    global team_lead
    
    # Entry for data
    n_row = pd.DataFrame(index = [0], columns = DATA_COLS)
    
    # get bowler and batter
    bowl, bat = desc_to_name(desc)
    
    # Find in dictionary
    if not bowl in bowls.keys():
        # Initialise bowler in dict
        bowls.update({bowl: [0,0,0]})
     
    if not bat in bats.keys():
        # Initialise batter in dict
        bats.update({bat: [0,0]})
        
        
    # Save data
    n_row['outcome'] = outcome
    
    n_row['innings'] = innings
    n_row['team_wkts'] = team_wkts
    n_row['team_score'] = team_score
    n_row['team_lead'] = team_lead
    
    n_row['bat_score'] = bats[bat][0]
    n_row['bat_balls'] = bats[bat][1]
    n_row['bat_avg'] = pregame_avgs[bat][0]
    
    n_row['bowl_balls'] = bowls[bowl][0]
    n_row['bowl_runs'] = bowls[bowl][1]
    n_row['bowl_wkts'] = bowls[bowl][2]     
    n_row['bowl_avg'] = pregame_avgs[bowl][1]
    
    
    
    # Update game situation and player states
    bowls[bowl][0] += 1
    
    if outcome[-1] == 'W':
        team_wkts += 1
        bowls[bowl][2] += 1
        bats[bat][1] += 1
        
    else:
        score = int(outcome[0])
        
        team_score += score
        team_lead += score

        # If not byes, update bowler figures                

        if outcome[-2:] == 'nb' or not outcome[-1] == 'b':
            bowls[bowl][1] += score
        
        # Check if delivery is legal
        if outcome[-1] == 'w' or outcome[-2:] == 'nb':

            # Check if extra runs scored off no ball
            if outcome[-2:] == 'nb' and int(score) > 1:
                bats[bat][0] += int(score) - 1
                
        else:
            if not outcome[-1] == 'b':
                bats[bat][0] += int(score)
                
            bats[bat][1] += 1



    return n_row



# storage of csv

def scrape_game(url, html):
    # Globals
    global bats
    global bowls
    global team_wkts
    global team_score
    global team_lead
    
    # Scorecard
    page = get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    
    # Determine date of start of match
    header = soup.find_all('div', class_ = 'sub-module gameHeader')[0]
    date = header.find_all('div', class_ = 'cscore_info-overview')[0].text.split(' ')
    month = date[-3]
    day = date[-2].split('-')[0]
    year = date[-1]
    date = day + "+" + month + "+" + year
    
    # Determine teams and order of innings
    all_scorecards = soup.find_all('article', class_ = 'sub-module scorecard')

    team1 = all_scorecards[0].find_all('a', class_ = '', role = "button")[0].text
    team2 = all_scorecards[1].find_all('a', class_ = '', role = "button")[0].text
    teams = [team1.split(' ')[0], team2.split(' ')[0]]
    inn_order = [0,1,None,None]
    
    # determine if follow on is enforced
    follow_on = (all_scorecards[2].find_all('a', class_ = '', role = "button")[0].text == team2 + " 2nd Innings (following on)")
    if follow_on:
        inn_order[2] = 1
    else:
        inn_order[2] = 0
        
    # check if third innings is played
    if len(all_scorecards) > 3:
        if follow_on:
            inn_order[3] = 0
        else:
            inn_order[3] = 1
        
        
    del team1, team2, follow_on
    
    pregame_avgs = {}
    
    


    players1, names1 = get_players(all_scorecards[0])
    players2, names2 = get_players(all_scorecards[1])
    
    for id in players1 + players2:
        # Access URL
        sg_url = "http://stats.espncricinfo.com/ci/engine/player/" + str(id) + ".html?class=1;spanmax1=" + date + ";spanval1=span;template=results;type=allround"
        page = get(sg_url)
        soup = BeautifulSoup(page.content, 'html.parser')
        
        # Get player name
        name = soup.find_all('div', class_ = 'icc-home')[0].text.split(' / ')[2]
        name = name.split(' ')[1]

        
        # Get correct table
        stats_table = soup.find_all('tr', class_ = 'data1')[1].find_all('td')
        
        if stats_table[1].get('class') == ['left']:
            bat = stats_table[5].text
            bowl = stats_table[9].text
        else:
            bat = stats_table[4].text
            bowl = stats_table[8].text
        
        
        try:
            bat = float(bat)
        except ValueError:
            pass
        
        try:
            bowl = float(bowl)
        except ValueError:
            pass
        
        pregame_avgs.update({name: [bat, bowl]})
    



    for inns in range(4):
        bats = {}
        bowls = {}
        team_wkts = 0
        
        # Determine team lead
        if inns == 0:
            team_lead = 0
        elif inn_order[inns - 1] != inn_order[inns]:
            team_lead *= -1
            
        team_score = 0
        
    
        i_html = html + str(inns + 1) + ".html" 
        # Ball by ball
        soup = BeautifulSoup(open(i_html).read(), 'html.parser')
    
        
        
        data = pd.DataFrame(columns = DATA_COLS)
        
        # get main window
        main_element = soup.find(id = 'main-container')
        comm_elems = main_element.find_all('div', class_='content match-commentary__content')[0]
        
        
        # organise all relevant commentary objects into one dataframe
        ind = -1
        ball = 0
        pd_overs = pd.DataFrame(columns = [1, 2, 3, 4, 5, 6])
        pd_temp = None
        
        for comm in comm_elems:
            
            # check for end of over
            if ball < 1:
                # append over to full dataframe
                if ind > -1:
                    pd_overs = pd_overs.append(pd_temp)
                
                # reset
                ind += 1
                ball = 6
                extras = 0
                pd_temp = pd.DataFrame(index = [ind], columns = [1, 2, 3, 4, 5, 6])
            
            
            if (comm.get('class') == ['commentary-item', '']) or (comm.get('class') == ['commentary-item', 'pre', '']) or (comm.get('class') == ['commentary-item', 'pre']):
                # check if delivery is an extra
                txt = comm.find('span', class_ = "over-score").text
                if txt[-1] == 'w' or txt[-2:] == 'nb':
                    # add extra delivery
                    pd_temp[10*ball + extras] = [comm]
                    
                    # add the column to pd_overs
                    if not 10*ball + extras in pd_overs.columns:
                        pd_overs[10*ball + extras] = [None] * len(pd_overs.index)
                    
                    extras += 1
                    
                else:
                    pd_temp.at[ind, ball] = comm
                    extras = 0
                    ball -= 1
            
        
        
        # Run through each delivery and reconstruct innings

        for k in reversed(pd_overs.index):  
            
            # get over
            over = pd_overs.loc[k]
            
            # For each ball
            for b in range(1,7):
 
                if over[b] == None:
                    break
                
                # Check for corresponding extra deliveries
                searching = True
                ind = 0
                while searching:
                    key = 10*b + ind 
                    if key in pd_overs.columns:
                        try:
                            # Parse illegal delivery
                            outcome = over[key].find('span', class_ = "over-score").text
                            desc = over[key].find('div', class_ = "description").text
                
                            # Add to main dataframe
                            data = data.append(data_row(outcome, desc, pregame_avgs, inns + 1), ignore_index = True)
        
                            ind += 1
                            
                        except AttributeError:
                            searching = False
                            
                    else:
                        searching = False
                
                
                # Parse legal delivery
                outcome = over[b].find('span', class_ = "over-score").text
                desc = over[b].find('div', class_ = "description").text
                
                
                
                # Add to main dataframe
                data = data.append(data_row(outcome, desc, pregame_avgs, inns + 1), ignore_index = True)
        
        
        # Export to CSV file
        if int(day) < 10:
            p_day = "0" + day
        
        # construct file name
        fname = p_day + NUM_MONTHS[month] + year + "-" + NAMES[teams[0]] + NAMES[teams[1]] + "-" + str(inns + 1) + NAMES[teams[inn_order[inns]]] + ".csv"
        
        print("Saving CSV to", fname)
        
        save_path = path.join(DIR, fname)
        data.to_csv(save_path, index = False)
            

    
    




scrape_game('https://www.espncricinfo.com/series/18659/scorecard/1152849/england-vs-australia-4th-test-icc-world-test-championship-2019-2021', r'C:\Users\liaml\Dropbox\Projects\TestMatch\Data Analysis\data\HTML Files\aus-eng-4th-test-2019-innings')
