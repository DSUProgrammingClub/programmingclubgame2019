#include "NcursesAPI/ncurses.h"

static int WIDTH = 20;
static int HEIGHT = 20;

static bool running = false;

static int prevPlayerX;
static int prevPlayerY;

static int playerX;
static int playerY;

void init() {
	Ncurses::init_ncurses();

	playerX = 2;
	playerY = 2;
	prevPlayerX = 2;
	prevPlayerY = 2;

	running = true;
}

void movePlayer(int xChange, int yChange) {
	int newX = playerX + xChange;
	int newY = playerY + yChange;

	if (newX <= 0 || newY <= 0 || newX >= WIDTH - 1 || newY >= HEIGHT - 1) {
		// dont move
	} else {
		prevPlayerX = playerX;
		prevPlayerY = playerY;
		playerX = newX;
		playerY = newY;
	}
}

void update() {
	timeout(20);
	int ch = getch();

	switch (ch) {
	case 'q':
		running = false;
		break;
	case 'w':
		movePlayer(0, -1);
		break;
	case 's':
		movePlayer(0, 1);
		break;
	case 'a':
		movePlayer(-1, 0);
		break;
	case 'd':
		movePlayer(1, 0);
		break;
	}
}

void render(Display& display) {
	display.DrawRectangle(0, 0, WIDTH, HEIGHT, '#', COLOR_RED, COLOR_YELLOW, false);

	display.DrawPoint(prevPlayerX, prevPlayerY, ' ', COLOR_BLACK, COLOR_WHITE);
	display.DrawPoint(playerX, playerY, '@', COLOR_BLACK, COLOR_WHITE);
}

int main() {
	init();

	Display main_display(WIDTH, HEIGHT);

	while (running) {
		update();
		render(main_display);
	}

	Ncurses::exit_ncurses();

	return 0;
}
