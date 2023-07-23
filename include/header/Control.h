#pragma once
#include <SDL.h>
#include "Pixel.h"

class Control
{
public:
	void HandleEvent(SDL_Event& e, Pixel& pixel);
private:
	PixelType drawType = PixelType::Sand;
	bool holdingKey;
	bool leftMouseButton;
};

