a.out: main.cpp
	g++ main.cpp NcursesAPI/ncurses.cpp -lncurses

all: a.out
