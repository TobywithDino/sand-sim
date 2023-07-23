#include <iostream>
#include <time.h>
#include "Sim.h"
#include "Pixel.h"

const int FPS = 60;
const int frameTime = 1000 / FPS;
Uint32 currentTime;//milliseconds
int shortFrameTime;
int fpsCounter;

int main(int argc, char* args[]) {
	srand(time(NULL));
	Sim* simulator = new Sim();
	simulator->init("Sand Simulator", false);
	while (simulator->running()) {
		currentTime = SDL_GetTicks();
		simulator->handleEvent();
		simulator->update();
		simulator->render();
		shortFrameTime = SDL_GetTicks() - currentTime;
		if (frameTime > shortFrameTime) {
			SDL_Delay(frameTime - shortFrameTime);
		}
		fpsCounter = SDL_GetTicks() - currentTime;
		//std::cout << shortFrameTime << " " << frameTime - shortFrameTime << std::endl;
		std::cout << round((float)1000/fpsCounter) << std::endl;
	}
	simulator->quit();
	return 0;
}