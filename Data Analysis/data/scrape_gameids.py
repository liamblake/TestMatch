from requests import get
from bs4 import BeautifulSoup


# Choose data to scrape down to here
DAY = 1
MONTH = 'Jan'
YEAR = 2000


# Construct URL
date = "+".join([str(DAY), MONTH, str(YEAR)])
url = "http://stats.espncricinfo.com/ci/engine/stats/index.html?class=1;orderby=start;orderbyad=reverse;spanmin1=" + date + ";spanval1=span;template=results;type=aggregate;view=results"
print(url)
