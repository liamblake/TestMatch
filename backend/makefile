INC = -I include #-I D:\MinGW\include
CC = g++
CFLAGS = $(INC) -D_GLIBCXX_USE_CXX11_ABI=0 
LDIR = D:\MinGW\lib
LIBS = -lm

_DEPS = hellomake.h


# Test scripts
fileio_test: test\fileio_test.cpp src\Player.cpp src\FileIO.cpp
	$(CC) -o build\fileio_test test\fileio_test.cpp src\Player.cpp src\FileIO.cpp $(CFLAGS)

arr_test: test\arr_test.cpp
	$(CC) -o build\arr_test test\arr_test.cpp $(CFLAGS)

time_test: test\time_test.cpp src\MatchTime.cpp src\rtnorm.cpp
	$(CC) -o build\time_test test\time_test.cpp src\MatchTime.cpp src\rtnorm.cpp $(CFLAGS)
