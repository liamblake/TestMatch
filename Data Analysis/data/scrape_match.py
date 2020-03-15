from pandas import DataFrame, Series
from requests import get
from bs4 import BeautifulSoup
from selenium import webdriver

from level_keys import BOWL_KEYS


# Each value to be extracted for each delivery
DATA_COLS = ['Outcome', 'Dismissal', 'Day', 'Innings', 'HostCountry', \
             'BatTeam', 'TeamWkts', 'TeamScore', 'TeamLead', \
             'Batter', 'BatScore', 'BatBalls', 'BatAvg', 'BatSR', 'BatArm', \
             'BowlTeam', 
             'Bowler', 'BowlBalls', 'BowlRuns', 'BowlWkts', 'BowlAvg', 'BowlSR', 'BowlType', \
             'SpellBalls', 'SpellRuns', 'SpellWkts', \
             'TossWin', 'TossElect', 'BatTeamTotalRuns', 'BatTeamTotalWkts', 'BowlTeamTotalRuns', 'BowlTeamTotalWkts', \
             'Commentary']


PLAYER_COLS = ['Initials', 'Surname', 'BatAvg',  'BatSR', 'BatArm', 'BowlAvg', 'BowlSR', 'BowlType', 'Team', 'Conflict']  
# Note: player stats are from BEFORE the start of the match




def driver_scroll_ballbyball(driver):
    """ Scrolls through ball-by-ball to fully load page.
        
        Modified version of accepted answer on
        https://stackoverflow.com/questions/48850974/selenium-scroll-to-end-of-page-in-dynamically-loading-webpage/48851166#48851166 

    """

    # Get scroll height.
    last_height = driver.execute_script("return document.body.scrollHeight")

    while True:

        # Scroll down to the bottom.
        driver.execute_script("window.scrollTo(0, 0);")
        sleep(0.25)
        driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
        sleep(1)

        # Calculate new scroll height and compare with last scroll height.
        new_height = driver.execute_script("return document.body.scrollHeight")

        if new_height == last_height:
              break


        last_height = new_height



def scrape_full_match(pd_row):
    
    def check_for_close():
        # Check if game conditions match close of play
        pass



    # Helper function - convert innings score to runs and wickets
    def add_score(string, total):
        # Remove '(f/o)' and 'd' from score
        string = string.replace('d', '')
        string = string.replace('(f/o)', '')

        score = string.split('/')
        runs = int(score[0])

        try:
            wkts = int(score[1])
        except IndexError:
            wkts = 10

        return [sum(i) for i in zip(total, [runs, wkts])]


    def get_players(soup):
        batters = soup.find_all('div', class_ = 'cell batsmen')
        ids = []
        urls = []
        names = []
        
        for b in batters:
            for r in b.find_all(href=True):
                url = r['href']
                urls.append(url)
                
                # Get ID from url
                ids.append(url.split('/')[-1][:-5])

        
        # Also include DNB
        dnb = soup.find_all('div', class_ = 'wrap dnb')[0]
        for r in dnb.find_all('a', href=True):
            url = r['href']
            urls.append(url)
            
            # Get ID from url
            ids.append(url.split('/')[-1][:-5])
            
        
        return(ids, urls)


    def get_player_stats(p_url, p_id):

        # Access URL
        sg_url = "http://stats.espncricinfo.com/ci/engine/player/" + str(p_id) + ".html?class=1;spanmax1=" + date + ";spanval1=span;template=results;type=allround"
        page = get(sg_url)
        soup = BeautifulSoup(page.content, 'html.parser')
        
        # Pandas series to return
        row = Series(index = PLAYER_COLS)

        # Get player name
        name = soup.find_all('div', class_ = 'icc-home')[0].text.split(' / ')[2]
        name = name.split(' ')
        row['Initials'] = name[0]
        row['Surname'] = name[1:]

        
        # Get correct table
        stats_table = soup.find_all('tr', class_ = 'data1')[1].find_all('td')
        
        if stats_table[1].get('class') == ['left']:
            row['BatAvg']  = stats_table[5].text
            row['BowlAvg'] = stats_table[9].text
        else:
            row['BatAvg'] = stats_table[4].text
            row['BowlAvg'] = stats_table[8].text


        # Get player batting hand and bowl type
        page = get(p_url)
        soup = BeautifulSoup(page.content, 'html.parser')

        bat_arm = None
        bowl_arm_txt = None
        for c in soup.find_all('p', class_ = 'ciPlayerinformationtxt'):
            if c.text[:13] == "Batting style":
                row['BatArm'] = c.text[14:]
            elif c.text[:13] == "Bowling style":
                bowl_arm_txt = c.text[14:]
                break

        try:
            row['BowlType'] = BOWL_KEYS[bowl_arm_txt]
        except KeyError:
            row['BowlType'] = "-"


        return row

    
    # Relabel row information
    match_id = pd_row['urlEnd']
    teams = pd_row[['Team1', 'Team2']]
    date = pd_row['StartDate'].replace(' ', '+')

    # Total runs scored and wickets lost for each team in entire game
    # Provides some measure of the pitch quality
    total1 = [0, 0]
    total2 = [0, 0]


    # Team1 always bats first
    team_bat = 0


    player_detail = DataFrame(columns = PLAYER_COLS)


    # Determine order of innings from prelimiary data
    inns_order = [0]
    total1 = add_score(pd_row['Score1'], total1)
    follow_on = False

    if pd_row['Score2'] != '-':
        inns_order.append(1)
        total2 = add_score(pd_row['Score2'], total2)

        if pd_row['Score3'] != '-':
            if pd_row['Score3'][-5:] == '(f/o)':
                # Follow-on enforced
                follow_on = True
                inns_order.append(1)
                total2 = add_score(pd_row['Score3'], total2)

            else:
                inns_order.append(0)
                total1 = add_score(pd_row['Score3'], total1)

            if pd_row['Score4'] != '-':
                if follow_on:
                    inns_order.append(0)
                    total1 = add_score(pd_row['Score4'], total1)

                else:
                    inns_order.append(1)
                    total2 = add_score(pd_row['Score4'], total2)

    # Nested if statements prevent unnessecary checking if game lasted less than 4 innings



    # Access scorecard page
    s_url = "https://www.espncricinfo.com/ci/engine/match/" + str(match_id) + ".html"
    page = get(s_url)
    soup = BeautifulSoup(page.content, 'html.parser')

    # Get close of play detail
    play_close = []

    # Get players
    play_ids, play_urls = get_players(soup)
    for p_id, p_url in zip(play_ids, play_urls):
        n_play = get_player_stats(p_id, p_url)
        player_detail = player_detail.append(n_play)



    #     # Access player profile


    #     # Statsguru request - get pregame states





    # Append match-global information to each entry
    host = pd_row['Country']














    # Determine the game situation when play was closed for each day





    # Format save string



    # Output data to 

    player_detail.to_csv('players_.csv', index = False)
