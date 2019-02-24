#include "NcursesAPI/ncurses.h"
#include "Perlin/Generator.hpp"
#include <vector>

const int WIDTH = 115;
const int HEIGHT = 31;

static bool running = false;

static int prevPlayerX;
static int prevPlayerY;

int playerX;
int playerY;

const int AMOUNT_OF_TILES = 4; // change in the future, just setting a template value

const static int OCTAVES = 3;
const static double PERSISTENCE = 0.55;
const static double LACUNARITY = 2.0;
const static double FREQUENCY = 0.8;

PerlinGenerator perlin;
static bool renderMap = true;

std::vector<std::vector<int> > map;
int playerMapX;
int playerMapY;

void init() {
	Ncurses::init_ncurses();

	srand( time(NULL) ); // also replace with seed for game session

	playerMapX = rand();
	playerMapY = rand();

	playerX = 2;
	playerY = 2;
	prevPlayerX = 2;
	prevPlayerY = 2;

	// Initialize the perlin noise generator
	perlin.SetSeed( time(NULL) );
	perlin.SetOctaveCount(OCTAVES);
	perlin.SetFrequency(FREQUENCY);
	perlin.SetLacunarity(LACUNARITY);
	perlin.SetPersistence(PERSISTENCE);

	perlin.GenerateMap();

	running = true;
}

void movePlayer(int xChange, int yChange) {
	int newX = playerX + xChange;
	int newY = playerY + yChange;

	if (newX <= 0){
		playerMapX -= WIDTH;
		playerX = WIDTH;
		perlin.GenerateMap();
		renderMap = true;
	} else if (newY <= 0){
		playerMapY -= HEIGHT;
		playerY = HEIGHT;
		perlin.GenerateMap();
		renderMap = true;
	} else if (newX > WIDTH){
		playerMapX += WIDTH;
		playerX = 1;
		perlin.GenerateMap();
		renderMap = true;
	} else if (newY > HEIGHT){
		playerMapY += HEIGHT;
		playerY = 1;
		perlin.GenerateMap();
		renderMap = true;
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
	//display.DrawRectangle(0, 0, WIDTH + 2, HEIGHT + 2, '#', COLOR_RED, COLOR_YELLOW, false);
	
	if (renderMap){
		perlin.RenderMap(display);
		renderMap = false;
	} else {
		perlin.RenderPoint(display, prevPlayerX - 1, prevPlayerY - 1);
	}

	display.DrawPoint(playerX, playerY, '@', COLOR_BLACK, COLOR_RED);
}

int main() {
	init();

	Display main_display(WIDTH+2, HEIGHT+2);

	while (running) {
		update();
		render(main_display);
	}

	Ncurses::exit_ncurses();

	return 0;
}
