#include <iostream>
#include "Sim.h"
#include "Pixel.h"
#include "Control.h"

const int Sim::SCALE = 8;
const int Sim::WIDTH = 640;//640/16 = 40
const int Sim::HEIGHT = 512;//512/16 = 32
SDL_Color* Sim::Background_Color = new SDL_Color();

Pixel* pixel;
Control* control;

Sim::Sim(){
	Background_Color->r = 10;
	Background_Color->g = 10;
	Background_Color->b = 10;
	Background_Color->a = 255;
}

void Sim::init(const char* title, bool fullScreen)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	int flags;
	fullScreen ? flags = 1 : flags = 0;//if fullScreen = true, flags = 1,else, flags = 0;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, flags);
	if (window != nullptr)
		std::cout << "window created successfully." << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetScale(renderer, SCALE, SCALE);
	if (renderer != nullptr)
		std::cout << "renderer created successfully." << std::endl;
	isRunning = true;
	pixel = new Pixel();
	control = new Control();
	//ground
	for (int i = 0; i <pixel->xBoarder; ++i) {
		for (int j = Pixel::yBoarder-1; j > Pixel::yBoarder - 3; --j) {
			pixel->world[Pixel::CoordToWorld(i,j)] = PixelType::Rock;
		}
	}

	/*
	for (int i = 40; i < 41; i++) {
		for (int j = 0; j < 62; j++) {
			pixel->world[Pixel::CoordToWorld(i, j)] = PixelType::Water;
		}
	}
	for (int i = 39; i < 40; i++) {
		for (int j = 0; j < 62; j++) {
			pixel->world[Pixel::CoordToWorld(i, j)] = PixelType::Sand;
		}
	}
	*/


}

void Sim::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type != SDL_QUIT) {
		//EVENTS
		control->HandleEvent(event, *pixel);
	}
	else
	{
		isRunning = false;
	}
}

void Sim::update()
{
	pixel->Update();
}

void Sim::render()
{
	SDL_SetRenderDrawColor(renderer, Background_Color->r, Background_Color->g, Background_Color->b, Background_Color->a);
	SDL_RenderClear(renderer);
	//render
	pixel->Render(renderer);
	SDL_RenderPresent(renderer);
}

void Sim::quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	pixel->world.clear();
	SDL_Quit();
	std::cout << "quit." << std::endl;
}
