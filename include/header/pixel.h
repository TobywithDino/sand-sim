#pragma once
#include <SDL.h>
#include <vector>
#include "Sim.h"
using std::vector;

enum class PixelType {
	Air,
	Sand,
	Water,
	Rock
};

class Pixel {
public:
	Pixel();
	vector<PixelType> world;//store all pixeltype in the world
	vector<bool> checked;
	void Update();
	void Render(SDL_Renderer* renderer);

	static int CoordToWorld(int x,int y); 

	static const int xBoarder;
	static const int yBoarder;
private:
	PixelType getPixelType(int indexInWorld);
	void sand(int indexInWorld);
	void water(int indexInWorld);
	void moveDown(int currentIndex, PixelType movingType);
	void moveDiagonally(int currentIndex, PixelType movingType);
	void moveHorizontally(int currentIndex, PixelType moingType);
	void swap(int indexA, int indexB);
};