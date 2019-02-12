#include <ncurses.h>
#include <iostream>

namespace Ncurses {
    void init_ncurses();
    void exit_ncurses();
}

class Display {
public:
	Display();
	Display(int width, int height);
	Display(int start_x, int start_y, int width, int height);
	Display(Display &parent, int start_x, int start_y, int width, int height);

	void Clear();
	void DrawRectangle(int x, int y, int width, int height, char ch, int back_color, int front_color, bool filled);
	void DrawRectangle(int x, int y, int width, int height, char* ch, int back_color, int front_color, bool filled);
	void DrawPoint(int x, int y, char ch, int back_color, int front_color);
	void DrawPoint(int x, int y, char* ch, int back_color, int front_color);

	~Display();

private:
	uint start_x;
	uint start_y;
	uint window_width;
	uint window_height;
	WINDOW * window;

	int findColorKey(int foreground, int background);
	bool contains(int x, int y);
};
