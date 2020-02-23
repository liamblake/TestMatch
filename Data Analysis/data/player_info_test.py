# -*- coding: utf-8 -*-
"""
Created on Sun Feb 23 17:50:53 2020

@author: liaml
"""

from bs4 import BeautifulSoup
from requests import get

p_url = "http://www.espncricinfo.com/australia/content/player/5334.html"

page = get(p_url)
soup = BeautifulSoup(page.content, 'html.parser')

for c in soup.find_all('p', class_ = 'ciPlayerinformationtxt'):
    if c.text[:13] == "Batting style":
        bat_arm = c.text[14:]
        print(bat_arm)
        
    if c.text[:13] == "Bowling style":
        bowl_arm = c.text[14:]
        print(bowl_arm)