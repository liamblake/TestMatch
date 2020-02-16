# -*- coding: utf-8 -*-
"""
Created on Sat Jan 25 11:28:06 2020



Assumptions
    - No more than 10 extras on any one legal delivery
    - No stumpings off wides


Each of these need to be addressed


"""


import pandas as pd
from bs4 import BeautifulSoup
from os import path

# Global variables
FILENAME = "04092019-AUSENG.csv"
DIR = path.dirname(path.realpath(__file__))

bats = {}
bowls = {}
innings = 1
team_wkts = 0
team_score = 0
team_lead = 0       # NEED TO CHANGE THIS


    

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


def data_row(outcome, desc):
    # Globals
    global bats
    global bowls
    global innings
    global team_wkts
    global team_score
    global team_lead
    
    # Entry for data
    n_row = pd.DataFrame(index = [0], columns = data.columns)
    
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


# Batsman averages BEFORE the match began, get these from Statsguru
pregame_avgs = {'Harris': [29.5, '-'],
                'Warner': [46.8, '-'],
                'Labuschagne': [38.45, 28.88],
                'Smith': [63.24, '-'],
                'Head': [45.72, '-'],
                'Wade': [28.02, '-'],
                'Paine': [31.20, '-'],
                'Cummins': [19.53, 21.48],
                'Starc': [22.27, 26.97],
                'Lyon': [11.8, 32.22],
                'Hazlewood': [12.77, 26.52],
                'Burns': [27.70, 33.75],
                'Denly': [24.33, 100],
                'Overton': [24.50, 42.28],
                'Root': [48.20, 52.15],
                'Roy': [16.75, '-'],
                'Stokes': [35.86, 32.22],
                'Bairstow': [35.83, '-'],
                'Buttler': [32.90, '-'],
                'Archer': [11.33, 13.53],
                'Broad': [19.09, 28.67],
                'Leach': [19.50, 25.04] }
# note that if a player does not bowl in the match, their bowling average
# does not need to be included



# scorecard URL details
url_base = 'https://www.espncricinfo.com/series/18659/commentary/1152849/england-vs-australia-4th-test-icc-world-test-championship-2019-2021'






# storage of csv
data = pd.DataFrame(columns = ['outcome', 'innings', 'team_wkts', 'team_score', 
                               'team_lead', 'bat_score', 'bat_balls', 'bat_avg', 
                               'bowl_balls', 'bowl_runs', 'bowl_wkts', 'bowl_avg'])




soup = BeautifulSoup(open("D:\liaml\Documents\Projects\Cricket Stats\ML Model\HTML Files\\aus-eng-4th-test-2019-innings1.html").read(), 'html.parser')


# get main window
main_element = soup.find(id = 'main-container')
comm_elems = main_element.find_all('div', class_='content match-commentary__content')[0]
overs = []


# organise all relevant commentary objects into one dataframe
ind = -1
ball = 0
pd_overs = pd.DataFrame(columns = [1, 2, 3, 4, 5, 6])
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
    
    
    if (comm.get('class') == ['commentary-item', '']) or (comm.get('class') == ['commentary-item', 'pre', '']):
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
                    data = data.append(data_row(outcome, desc), ignore_index = True)

                    ind += 1
                    
                except AttributeError:
                    searching = False
                    
            else:
                searching = False
        
        
        # Parse legal delivery
        outcome = over[b].find('span', class_ = "over-score").text
        desc = over[b].find('div', class_ = "description").text
        
        # Add to main dataframe
        data = data.append(data_row(outcome, desc), ignore_index = True)

# Export to CSV file
save_path = path.join(DIR, FILENAME)
data.to_csv(save_path, index = False)
    

