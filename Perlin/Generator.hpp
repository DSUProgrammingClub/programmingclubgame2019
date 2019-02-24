#include <iostream>
#include <vector>
#include "noise/noise.h"

extern const int WIDTH;
extern const int HEIGHT;

extern const int AMOUNT_OF_TILES;

extern std::vector<std::vector<int> > map;
extern int playerMapX;
extern int playerMapY;
extern int playerX;
extern int playerY;

class PerlinGenerator {
private:
	noise::module::Perlin pnoise;
	double SCALE;

public:
	PerlinGenerator();
	PerlinGenerator(int, int, double, double, double);
	void SetSeed(int);
	void SetFrequency(double);
	void SetLacunarity(double);
	void SetPersistence(double);
	void SetOctaveCount(int);
	int GetNoise(int, int);
	void GenerateMap();
	void RenderMap(Display&);
	void RenderPoint(Display&, int, int);
};

PerlinGenerator::PerlinGenerator(){
	this->SCALE = 50.0;
}

PerlinGenerator::PerlinGenerator(int s, int o, double f, double l, double p){
	this->SCALE = 50.0;
	this->SetSeed(s);
	this->SetOctaveCount(o);
	this->SetFrequency(f);
	this->SetLacunarity(l);
	this->SetPersistence(p);
}

void PerlinGenerator::SetSeed(int seed){
	this->pnoise.SetSeed(seed);
}

void PerlinGenerator::SetFrequency(double frequency){
	this->pnoise.SetFrequency(frequency);
}

void PerlinGenerator::SetLacunarity(double lacunarity){
	this->pnoise.SetLacunarity(lacunarity);
}

void PerlinGenerator::SetPersistence(double persistence){
	this->pnoise.SetPersistence(persistence);
}

void PerlinGenerator::SetOctaveCount(int octaves){
	this->pnoise.SetOctaveCount(octaves);
}

int PerlinGenerator::GetNoise(int x, int y){
	// Grab a value from (playerMapX, playerMapY, 0.0) from the perlin noise generator
	double noiseValue = this->pnoise.GetValue((double)(playerMapX + x) / this->SCALE, (double)(playerMapY + y) / this->SCALE, 0.0);

	// normalize value between -1 and 1 (required even though it shouldnt be)
	if (noiseValue > 1)
		noiseValue = 1;
	else if (noiseValue < -1)
		noiseValue = -1;

	noiseValue = (noiseValue + 1) / 2; // normalize the value between 0 and 1
	noiseValue = floor(noiseValue * AMOUNT_OF_TILES); // decide which tile this position will be
	
	// in the rare case that noiseValue is exactly equal to amount of tiles, subtract 1
	if (noiseValue == AMOUNT_OF_TILES)
		noiseValue--;

	return (int)noiseValue;
}

void PerlinGenerator::GenerateMap(){
	if (map.size() == 0){
		// Initialize the map if it doesnt contain values
		for (int i = 0; i < HEIGHT; i++){
			map.push_back(std::vector<int>());
			for (int j = 0; j < WIDTH; j++){
				map[i].push_back(this->GetNoise(j, i));
			}
		}
	} else {
		// fill the map with new values
		for (int i = 0; i < HEIGHT; i++){
			for (int j = 0; j < WIDTH; j++){
				map[i][j] = this->GetNoise(j, i);
			}
		}
	}
}

void PerlinGenerator::RenderMap(Display& display){
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			this->RenderPoint(display, j, i);
		}
	}
}

void PerlinGenerator::RenderPoint(Display& display, int x, int y){
	// Dont render this point if is in the same spot as the player because a blinking effect will happen
	if (x == playerY - 1 && y == playerX - 1)
		return;
	
	// use the tile number of this specific cell in the map to pick the color and character to render
	char ch = 'X';
	int color;
	switch (map[y][x]){
		case 0:
			color = COLOR_BLUE;
			break;
		case 1:
			color = COLOR_GREEN;
			break;
		case 2:
			color = COLOR_RED;
			break;
		case 3:
			color = COLOR_WHITE;
			break;
	}

	// draw the point to the display
	display.DrawPoint(x+1, y+1, ch, COLOR_BLACK, color);
}
