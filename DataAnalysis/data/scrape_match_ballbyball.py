from selenium import webdriver

# Each value to be extracted for each delivery
DATA_COLS = ['Outcome', 'Dismissal', 'Day', 'Innings', 'HostCountry', \
             'BatTeam', 'TeamWkts', 'TeamScore', 'TeamLead', \
             'Batter', 'BatScore', 'BatBalls', 'BatAvg', 'BatSR', 'BatArm', \
             'BowlTeam', 
             'Bowler', 'BowlBalls', 'BowlRuns', 'BowlWkts', 'BowlAvg', 'BowlSR', 'BowlType', \
             'SpellBalls', 'SpellRuns', 'SpellWkts', \
             'TossWin', 'TossElect', 'BatTeamTotalRuns', 'BatTeamTotalWkts', 'BowlTeamTotalRuns', 'BowlTeamTotalWkts', \
             'Commentary']



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