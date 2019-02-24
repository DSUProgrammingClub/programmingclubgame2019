a.out: main.cpp
	g++ main.cpp NcursesAPI/ncurses.cpp -lncurses -LPerlin/noise/lib/ -O2 -lnoise

all: a.out
