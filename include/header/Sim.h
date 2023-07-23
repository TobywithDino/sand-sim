#pragma once
#include <SDL.h>


class Sim {
public:
	Sim();
	void init(const char* title, bool fullScreen);
	void handleEvent();
	void update();
	void render();
	void quit();
	bool running() { return isRunning; }
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	static const int SCALE;
	static const int WIDTH;
	static const int HEIGHT;
	static SDL_Color* Background_Color;
private:
	bool isRunning = false;
};