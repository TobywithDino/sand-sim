#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 360

static SDL_Window* window;
static SDL_Renderer* renderer;
int lastTick;
bool running;
void handleEvent();
void update();
void render();

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("sand-sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    lastTick = 0;
    running = true;
    while(running){
        handleEvent();
        if(SDL_GetTicks64() - lastTick > 1000/120){
            update();
            render();
        }
    }

    return 0;
}

void handleEvent(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
        }
    }
}

void update(){

}

void render(){
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}