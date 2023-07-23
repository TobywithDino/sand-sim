#include <iostream>
#include "Pixel.h"
#include "Sim.h"

const int Pixel::xBoarder = Sim::WIDTH / Sim::SCALE;
const int Pixel::yBoarder = Sim::HEIGHT / Sim::SCALE;
Pixel::Pixel()
{
	world = vector<PixelType>(xBoarder * yBoarder, PixelType::Air);
	checked = vector<bool>(xBoarder * yBoarder, false);
}

void Pixel::Update()
{
	for (int i = 0; i < checked.size(); ++i) {
		checked[i] = false;
	}

	for (int i = world.size() - 1; i >= 0; --i) {
		if (!checked[i]) {
			switch (world[i]) {
			case PixelType::Sand:
				sand(i);
				break;
			case PixelType::Water:
				water(i);
				break;
			default:
				break;
			}
		}
	}
}

void Pixel::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < xBoarder; ++i) {
		for (int j = 0; j < yBoarder; ++j) {
			SDL_Rect rec;
			rec.x = i;
			rec.y = j;
			rec.w = 1;
			rec.h = 1;
			switch (world[CoordToWorld(i,j)]) {
			case PixelType::Air:
				//SDL_SetRenderDrawColor(renderer, Sim::Background_Color->r, Sim::Background_Color->g, Sim::Background_Color->b, Sim::Background_Color->a);
				break;
			case PixelType::Sand:
				SDL_SetRenderDrawColor(renderer, 212, 155, 49, 255);
				SDL_RenderFillRect(renderer, &rec);
				break;
			case PixelType::Water:
				SDL_SetRenderDrawColor(renderer, 0, 170, 255, 255);
				SDL_RenderFillRect(renderer, &rec);
				break;
			case PixelType::Rock:
				SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
				SDL_RenderFillRect(renderer, &rec);
				break;
			default:
				break;
			}
		}
	}
}

PixelType Pixel::getPixelType(int indexInWorld)
{
	PixelType type;
	type = world[indexInWorld];
	return type;
}

int Pixel::CoordToWorld(int x, int y)
{
	int worldIndex;
	worldIndex = (x + xBoarder * y);
	return worldIndex;
}

void Pixel::sand(int indexInWorld) {
	if (indexInWorld + xBoarder >= world.size())
		return;
	PixelType targetType = world[indexInWorld + xBoarder];
	switch (targetType) {
	case PixelType::Air:
		moveDown(indexInWorld, PixelType::Sand);
		break;
	case PixelType::Rock:
		moveDiagonally(indexInWorld, PixelType::Sand);
		break;
	case PixelType::Sand:
		moveDiagonally(indexInWorld, PixelType::Sand);
		break;
	case PixelType::Water:
		swap(indexInWorld, indexInWorld + xBoarder);
		break;
	default:
		break;
	}
}

void Pixel::water(int indexInWorld){
	if(indexInWorld + xBoarder < world.size()) {
		PixelType targetType = world[indexInWorld + xBoarder];
		if (targetType == PixelType::Air) {
			moveDown(indexInWorld, PixelType::Water);
			return;
		}	
	}
	moveHorizontally(indexInWorld, PixelType::Water);
}

void Pixel::moveDown(int currentIndex, PixelType movingType)
{
	if (currentIndex + xBoarder >= world.size())
		return;
	world[currentIndex + xBoarder] = movingType;
	world[currentIndex] = PixelType::Air;
	checked[currentIndex + xBoarder] = true;
}

void Pixel::moveDiagonally(int currentIndex, PixelType movingType)
{
	if (currentIndex + xBoarder >= world.size())
		return;
	int x = currentIndex;
	PixelType targetType;
	while (x >= xBoarder) {
		x -= xBoarder;
	}
	if (x == 0) {
		//when left is out of width
		targetType = world[currentIndex + xBoarder + 1];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex + xBoarder + 1] = movingType;
			checked[currentIndex + xBoarder + 1] = true;
		}
		return;
	}
	else if (x == xBoarder - 1) {
		//when right is out of width
		targetType = world[currentIndex + xBoarder - 1];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex + xBoarder - 1] = movingType;
			checked[currentIndex + xBoarder - 1] = true;
		}
		return;
	}
	int r = rand() % 2;//x = 0 or 1
	if (r==0)
		r = -1;
	targetType = world[currentIndex + xBoarder + r];
	if (targetType == PixelType::Air) {
		world[currentIndex] = PixelType::Air;
		world[currentIndex + xBoarder + r] = movingType;
		checked[currentIndex + xBoarder + r] = true;
	}
	else {
		targetType = world[currentIndex + xBoarder - r];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex + xBoarder - r] = movingType;
			checked[currentIndex + xBoarder - r] = true;
		}
	}
}

void Pixel::moveHorizontally(int currentIndex, PixelType movingType)
{
	int x = currentIndex;
	PixelType targetType;
	while (x >= xBoarder) {
		x -= xBoarder;
	}
	if (x == 0) {
		//when left is out of width
		targetType = world[currentIndex + 1];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex + 1] = movingType;
			checked[currentIndex + 1] = true;
		}
		return;
	}
	else if (x == xBoarder - 1) {
		//when right is out of width
		targetType = world[currentIndex - 1];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex - 1] = movingType;
			checked[currentIndex - 1] = true;
		}
		return;
	}
	int r = rand() % 2;//x = 0 or 1
	if (r == 0)
		r = -1;
	targetType = world[currentIndex + r];
	if (targetType == PixelType::Air) {
		world[currentIndex] = PixelType::Air;
		world[currentIndex + r] = movingType;
		checked[currentIndex + r] = true;
	}
	else {
		targetType = world[currentIndex - r];
		if (targetType == PixelType::Air) {
			world[currentIndex] = PixelType::Air;
			world[currentIndex - r] = movingType;
			checked[currentIndex - r] = true;
		}
	}
}

void Pixel::swap(int indexA, int indexB)
{
	PixelType temp = world[indexA];
	world[indexA] = world[indexB];
	world[indexB] = temp;
	//make these two pixel checked because they are maybe not air
	checked[indexA] = true;
	checked[indexB] = true;
}
