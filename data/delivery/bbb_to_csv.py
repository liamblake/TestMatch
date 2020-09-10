from pandas import DataFrame, Series, read_csv
from yaml import safe_load
from os import path, fsencode, fsdecode, listdir

# Each value to be extracted for each delivery
DATA_COLS = ['Outcome', 'Dismissal', 'Innings', 'HostCountry', \
             'InnBalls', 'BatTeam', 'TeamWkts', 'TeamScore', 'TeamLead', \
             'Batter', 'BatPosition', 'BatScore', 'BatBalls', 'BatAvg', 'BatSR', 'BatArm', \
             'BowlTeam', \
             'Bowler', 'BowlBalls', 'BowlRuns', 'BowlWkts', 'BowlAvg', 'BowlSR', 'BowlType', \
             'SpellBalls', 'SpellRuns', 'SpellWkts', \
             'TossWin', 'TossElect', 'BatTeamTotalRuns', 'BatTeamTotalWkts', 'BowlTeamTotalRuns', 'BowlTeamTotalWkts', \
             'Commentary']

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

NUM_MONTHS = {'01': 'Jan', \
              '02': 'Feb', \
              '03': 'Mar', \
              '04': 'Apr', \
              '05': 'May', \
              '06': 'Jun', \
              '07': 'Jul', \
              '08': 'Aug', \
              '09': 'Sep', \
              '10': 'Oct', \
              '11': 'Nov', \
              '12': 'Dec'}    

DIR = path.dirname(path.realpath(__file__))

# Load match list
MATCHES = read_csv(DIR + "/match_list.csv")



def concat_bbb_stats(yaml_dir):
    # Load YAML file
    with open(yaml_dir, "r") as stream:
        data = safe_load(stream)

    # Match info
    info = data['info']
    print(info)

    teams = info['teams']
    start_date = (info['dates'])[0]
    start_date = start_date.isoformat()
    start_date_list = start_date.split("-")
    date_format = start_date_list[2] + " " + NUM_MONTHS[start_date_list[1]] + " " + start_date_list[0]

    home_team = COUNTRY_CODES[teams[0]]
    away_team = COUNTRY_CODES[teams[1]]

    possible_matches = MATCHES.query('Team1 == "home_team" & Team2 == "away_team" & StartDate == "date_format"')
    print(possible_matches)

    


    # Create dataframe for output
    output = DataFrame(columns = DATA_COLS)

    
    lead = 0

    # Each innings
    return
    for inns in (data['innings']).items():
        inn_num = (inns[0])[0]


    # Fill in match information









# Create output .csv file

# Loop through each file in ballbyball directory
bbb_dir = fsencode(DIR + "/ballbyball")

print(MATCHES)

for file in listdir(bbb_dir):
    name = fsdecode(file)
    print(name)

    concat_bbb_stats(DIR + "/ballbyball/" + name)
    break