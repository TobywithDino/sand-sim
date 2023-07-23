#pragma once
#include <SDL2/SDL.h>
#include "header/Pixel.h"

class Control
{
public:
	void HandleEvent(SDL_Event& e, Pixel& pixel);
private:
	PixelType drawType = PixelType::Sand;
	bool holdingKey;
	bool leftMouseButton;
};

