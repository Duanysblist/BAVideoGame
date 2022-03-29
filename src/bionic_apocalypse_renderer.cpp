#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

//Window and image variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* player;
SDL_Texture* enemy;
SDL_Rect player_rect = { getPlayerScreenPositionX(), getPlayerScreenPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT };
SDL_Rect enemy_rect = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };


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
    window = SDL_CreateWindow("Bionic Apocalypse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    
    SDL_Surface* image = IMG_Load("../resource/player_texture.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    player = SDL_CreateTextureFromSurface(renderer, image);
    if (player == NULL) csci437_error("Could not create texture from surface!");
    image = IMG_Load("../resource/enemy_texture.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    enemy = SDL_CreateTextureFromSurface(renderer, image);
    if (player == NULL) csci437_error("Could not create texture from surface!");
}

void window_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void window_update() {
    // Draw line for bottom bar
    thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 50);

    SDL_RenderPresent(renderer);
}

void drawPlayer() {
    player_rect = { getPlayerScreenPositionX(), getPlayerScreenPositionY(), 100, 100 };
    SDL_RenderCopyEx(renderer, player, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
}

void drawEnemy(Enemy* foe) {
    enemy_rect = { foe->getX(), foe->getY(), 100, 100 };
    SDL_RenderCopyEx(renderer, enemy, NULL, &enemy_rect, 0, NULL, SDL_FLIP_NONE);
}