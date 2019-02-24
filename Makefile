a.out: main.cpp
	g++ main.cpp NcursesAPI/ncurses.cpp -lncurses -Lnoise/lib/ -O2 -lnoise

all: a.out
