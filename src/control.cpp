#include "Control.h"
#include "Sim.h"
#include <iostream>

void Control::HandleEvent(SDL_Event& e, Pixel& pixel)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			drawType = PixelType::Sand;
			break;
		case SDLK_2:
			drawType = PixelType::Water;
			break;
		case SDLK_3:
			drawType = PixelType::Rock;
			break;
		default:
			break;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		leftMouseButton = e.button.button == 1;
		holdingKey = true;
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		holdingKey = false;
	}
	if (holdingKey) {
		int x;
		int y;
		SDL_GetMouseState(&x, &y);
		x /= Sim::SCALE;
		y /= Sim::SCALE;
		if (x >= Pixel::xBoarder || x < 0 || y < 0 || y >= Pixel::yBoarder)
			return;
		if(leftMouseButton)
			pixel.world[Pixel::CoordToWorld(x, y)] = drawType;
		else
			pixel.world[Pixel::CoordToWorld(x, y)] = PixelType::Air;
	}
}
