INC = -I ..\include -I D:\boost\boost_1_73_0 #-I D:\MinGW\include
CC = g++
CFLAGS = $(INC) -D_GLIBCXX_USE_CXX11_ABI=0 
LDIR = D:\MinGW\lib
LIBS = -lm

player: ctest_player.cpp 
	$(CC) ctest_player.cpp ..\src\Player.cpp -o ..\build\ctest_player $(CFLAGS)
