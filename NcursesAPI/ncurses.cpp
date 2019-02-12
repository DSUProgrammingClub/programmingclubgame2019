#include "ncurses.h"

namespace Ncurses {
	void init_ncurses() {
		initscr();
		raw();
		noecho();
		curs_set(FALSE);

		if(has_colors() == FALSE){
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
		}

		start_color();
		refresh();

		for(int i = 0; i < 8; i++){
			for(int x = 0; x < 8; x++){
				init_pair(i*10+x, i, x);
			}
		}
	}

	int get_char() {
		return getch();
	}

	void exit_ncurses() {
		endwin();
	}
}




Display::Display() {
	window = newwin(10, 10, 0, 0);
	start_x = 0;
	start_y = 0;
	window_height = window_width = 10;
	box(window, 0, 0);
	wrefresh(window);
}

Display::Display(int width, int height) {
	window = newwin(width, height, 0, 0);
	this->window_height = height;
	this->window_width = width;
	this->start_x = 0;
	this->start_y = 0;
	box(window, 0, 0);
	wrefresh(window);
}

Display::Display(int start_x, int start_y, int width, int height) {
	this->start_x = start_x;
	this->start_y = start_y;
	this->window_height = height;
	this->window_width = width;
	window = newwin(width, height, start_y, start_x);
}

Display::Display(Display &parent, int start_x, int start_y, int width, int height) {
	this->start_x = parent.start_x + start_x;
	this->start_y = parent.start_y + start_y;
	this->window_width = width;
	this->window_height = height;

	window = newwin(this->start_y, this->start_x, height, width);
}


Display::~Display() {
}

void Display::Clear() {
	wattron(window,findColorKey(COLOR_BLACK, COLOR_BLACK));
	for (int i = 1; i < window_height-1; i++) {
		for (int x = 1; x < window_width-1; x++) {
			mvwprintw(window, i, x, " ");
		}
	}

	wattroff(window,findColorKey(COLOR_BLACK,COLOR_BLACK));
	wrefresh(window);
}

void Display::DrawRectangle(int x, int y, int w, int h, char ch, int back_color, int front_color, bool filled) {
	if (!contains(x,y) || !contains(x+w-1, y+h-1)) {
		return;
	}

	int colorKey = findColorKey(front_color, back_color);
	char cha[2] = {ch,0};

	if(colorKey != -1)
		wattron(window,COLOR_PAIR(colorKey));

	if (filled) {
		for (int i = 0; i < h; i++) {
			for (int p = 0; p < w; p++) {
				mvwprintw(window, y+i, x+p, cha);
			}
		}
	}
	else {
		for (int i = 0; i < h; i++) {
			for (int p = 0; p < w; p++) {
				if (i == 0 || p == 0 || i == h-1 || p == w-1)
					mvwprintw(window, y+i, x+p, cha);
			}
		}		
	}
	if (colorKey != -1)
		wattroff(window,COLOR_PAIR(colorKey));

	wrefresh(window);
}

void Display::DrawPoint(int x, int y, char ch, int back_color, int front_color) {
	if (!contains(x,y)) {
		return;
	}

	char cha[2] = {ch,0};
	int colorKey = findColorKey(front_color, back_color);

	if (colorKey != -1)
		wattron(window,COLOR_PAIR(colorKey));
	mvwprintw(window, y, x, cha);
	if (colorKey != -1)
		wattroff(window,COLOR_PAIR(colorKey));
	wrefresh(window);
}

int Display::findColorKey(int foreground, int background) {
	if (foreground >= 8 || background >= 8) {
		return -1;
	}
	return foreground * 10 + background;
}

bool Display::contains(int x, int y) {
	if (x < 0 || y < 0 || x >= window_width || y >= window_height)
		return false;
	else
		return true;
}