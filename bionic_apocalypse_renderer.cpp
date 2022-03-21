#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//Window and image variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Rect player_rect = { getPlayerScreenPositionX(), getPlayerScreenPositionY(), 100, 100 };


void csci437_error(const std::string& msg)
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void csci437_img_error(const std::string& msg)
{
    std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
    exit(0);
}

void csci437_ttf_error(const std::string& msg)
{
    std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
    exit(0);
}
 
void window_startup() {
	/*** Initialization ***/

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) csci437_error("SDL could not initialize!");

    // Create window
    window = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) csci437_error("Window could not be created!");

    // Init Bitmap loading
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) csci437_img_error("SDL could not initialize bitmap loaders!");

    // init TTF
    if (TTF_Init() < 0) csci437_ttf_error("Unable to initialize TTF!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) csci437_error("Unable to create renderer!");
    
    SDL_Texture* player;
}

void window_update() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}