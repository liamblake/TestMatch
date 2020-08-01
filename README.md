# TestMatch
A data-driven simulator of test cricket, built upon historical ball-by-ball data to simulate a full match. The simulation itself is built in C++


## Setup
The project is currently not in a useable state, but once it is more developed this section will outline how to get the simulator working.


## Dependencies
The source code relies upon the following C++ libraries:
* GNU Scientific Library, available from several different sources. This project uses a Windows version available [here](test).


## Breakdown
Loosely, the project is broken into several smaller goals:
* Developing a model for ball-by-ball simulation, in Python via data scraped from ESPNCricInfo.
* Developing the simulation backend itself in C++, initially as a console program outputting to a custom file format.
* Designing and developing a GUI using the Qt library, to make the tool easier to use. 
See the 


## Sources & Acknowledgements
This project was inspired by Jamee999's test cricket simulator written in Python. I wanted to create a more robust and detailed simulator based upon real data. I also make use of code provided by the following developers:
* Guillaume Dollé, Vincent Mazet (LSIIT, CNRS/Université de Strasbourg), for an implementation of sampling from a truncated normal distribution used to randomly determine the amount of time taken by game events. Responsible for `rtnorm.h` and `rtnorm.cpp`, available [here](link)
*