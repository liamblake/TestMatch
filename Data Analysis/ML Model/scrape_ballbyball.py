# -*- coding: utf-8 -*-
"""
Created on Sat Jan 25 11:28:06 2020

@author: liaml
"""


import pandas as pd
from re import search
from bs4 import BeautifulSoup
from numpy import floor

def bat_li_to_strings(li):
    text = li.text

    m = search(r"\d", text)
    name = text[0:m.start()]
    name = name.split(' ')[1]
    score = text[m.start():]
    
    runs = score.split(' ')[0]
    balls = score.split(' ')[1]
    balls = balls[1:-2]
    
    return name, int(runs), int(balls)


def bowl_li_to_strings(li):
    text = li.text

    m = search(r"\d", text)
    name = text[0:m.start()]
    name = name.split(' ')[1]
    score = text[m.start():]
    
    overs = score.split('-')[0]
    runs = score.split('-')[2]
    wkts = score.split('-')[3]
    
    balls = 6*floor(float(overs)) + 10*(float(overs) - floor(float(overs)))
    return name, int(balls), int(runs), int(wkts)



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



score1 = 0
score2 = 0
lead1 = 0
lead2 = 0

# For each innings

soup = BeautifulSoup(open("D:\liaml\Documents\Projects\Cricket Stats\ML Model\HTML Files\\aus-eng-4th-test-2019-innings1.html").read(), 'html.parser')


# get main window
main_element = soup.find(id = 'main-container')
comm_elems = main_element.find_all('div', class_='content match-commentary__content')[0]
overs = []


# group each over into one
index = 0
ball = 7
pd_overs = pd.DataFrame(index = range(127), columns = ['end', 1, 2, 3, 4, 5, 6])
for comm in comm_elems:
    # check for end of over
    if ball < 1:
        index += 1
        ball = 6
    
    # end of over module
    if (comm.get('class') == ['commentary-item', 'end-of-over']):
        pd_overs.loc[index]['end'] = comm
    
    if (comm.get('class') == ['commentary-item', '']) or (comm.get('class') == ['commentary-item', 'pre', '']):
        pd_overs.iloc[index].loc[ball] = comm
        ball -= 1
    


bat1_runs = 0
bat2_runs = 0
bat1_ball = 0
bat2_ball = 0

bowl_balls = 0
bowl_runs = 0
bowl_wkts = 0


for k in reversed(pd_overs.index):  
    # get not out batsmen at end of over
    columns = pd_overs.loc[k]['end'].find_all('ul', class_ = 'two-col-table')
    batters = columns[0].find_all('li')
    

    bat1, bat1_runs, bat1_ball = bat_li_to_strings(batters[0])
    if len(batters) > 1:
        bat2, bat2_runs, bat2_ball = bat_li_to_strings(batters[1])
    else:
        bat2, bat2_runs, bat2_ball = None, None, None
    strike = False
    
    
    # get bowler
    bowler = columns[1].find_all('li')[0]
    bowl, bowl_balls, bowl_runs, bowl_wkts = bowl_li_to_strings(bowler)
    
    over_states = pd.DataFrame(index = range(1,7), columns = data.columns)
    over_states.loc[:]['bowl_avg'] = pregame_avgs[bowl][1]
    
    # store in dataframe
    batters = pd.DataFrame(index = [bat1, bat2], columns = ['runs', 'balls'], \
                           data = [[bat1_runs, bat1_ball], [bat2_runs, bat2_ball]])

    
    # free up memory
    del bat1, bat2, bat1_runs, bat2_runs, bat1_ball, bat2_ball

    
    print("=======")
    # work backwards from last ball, correcting states
    for i in range(6,0, -1):
        
        # get outcome of ball
        out = pd_overs.loc[k][i].find('span', class_ = "over-score").text
        #over_states.loc[i]['outcome'] = out
        print(out)
# =============================================================================
#         # if wicket, find out batsman
#         if out == 'W':
#             # find the dismissed batsman
#             desc = pd_overs.loc[k][i].find('p', class_ = "dismissal").text.split(' ')
#             
#             # determine the next in batsman, this one is replaced
#             try:
#                 print(pd_overs.loc[k][i+1].find('div', class_ = "description"))
#                 next_in = pd_overs.loc[k][i+1].find('div', class_ = "description").text.split(' ')[2][:-1]
#                 print(next_in)
#             except IndexError:
#                 print("index error", i)
#             
#             bowl_wkts -= 1
# =============================================================================
            

        
            
        # save to dataframe
            
    
    
    data = data.append(over_states, ignore_index = True)



display(data)   
    
    
    
    


     
        

