from bs4 import BeautifulSoup
import pandas as pd

soup = BeautifulSoup(open("page_source.html"), 'html.parser')

# get main window
main_element = soup.find(id = 'main-container')
comm_elems = main_element.find_all('div', class_='content match-commentary__content')[0]

# organise all relevant commentary objects into one dataframe
ind = -1
ball = 0
pd_overs = pd.DataFrame(columns = [1, 2, 3, 4, 5, 6])
pd_temp = None
loop = 0
for comm in comm_elems.find_all('div', class_ = 'item-wrapper'):
    
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

pd_overs = pd_overs.append(pd_temp)
print([x.text for x in pd_overs[6]])