INC = -I include -I D:\MinGW\include
CC = g++
CFLAGS = $(INC)
LDIR = D:\MinGW\lib
LIBS = -lm

_DEPS = hellomake.h

time_test: test\time_test.cpp src\MatchTime.cpp src\rtnorm.cpp
	$(CC) -o build\time_test test\time_test.cpp src\MatchTime.cpp src\rtnorm.cpp $(CFLAGS)
