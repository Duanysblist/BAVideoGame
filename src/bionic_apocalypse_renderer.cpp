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
#include <cmath>

//Window and image variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* player;
SDL_Texture* enemy;
SDL_Rect player_rect = { getPlayerScreenPositionX(), getPlayerScreenPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT };
SDL_Rect enemy_rect = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
TTF_Font* font;
SDL_Texture* texture;
SDL_Color color = { 255, 255, 255 };
int BAR_LENGTH = 200;
int BAR_START = 30;

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

    font = TTF_OpenFont("../resource/Arial.ttf", 18);
    if (font == NULL) csci437_error("Unable to open font!");
}

void window_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void drawPlayer(const bool world) {
    if (world) {
        player_rect = { getPlayerScreenPositionX(), getPlayerScreenPositionY(), 100, 100 };
        SDL_RenderCopyEx(renderer, player, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }
    else {
        player_rect = {0, 500, 100, 100};
        SDL_RenderCopyEx(renderer, player, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }
}

void drawEnemy(Enemy* foe) {
    enemy_rect = { foe->getX(), foe->getY(), 100, 100 };
    SDL_RenderCopyEx(renderer, enemy, NULL, &enemy_rect, 0, NULL, SDL_FLIP_NONE);
}

void drawText(const char* words, int dst_x, int dst_y, int r, int g, int b) {
    SDL_Surface* text = TTF_RenderText_Solid( font, words, color );
    if ( text == NULL ) csci437_ttf_error("Unable to render text!");
    texture = SDL_CreateTextureFromSurface( renderer, text );
    if(texture == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect dst = { dst_x, dst_y, text->w, text->h};
    SDL_Point rot = {text->w/2, text->h/2};
    SDL_SetTextureColorMod( texture, r, g, b );
    SDL_RenderCopyEx( renderer, texture, NULL, &dst, 0, &rot, SDL_FLIP_NONE );
}

void drawHealthBar() {
    double player_health = getPlayerHealth();
    double health_length = (player_health/MAX_HEALTH)*BAR_LENGTH;
    // outline of bar
    rectangleRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + BAR_LENGTH, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 255, 255, 255);
    // interior bar representing health
    boxRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + health_length, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 0, 0, 128);
    // write health under bar
    drawText("Health: ", BAR_START + 50, SCREEN_HEIGHT - 30, 255, 255, 255);
    int health = trunc(player_health);
    drawText((std::to_string(health)).c_str(), BAR_START + 120, SCREEN_HEIGHT - 30, 255, 255, 255);
}

void drawInventory() {
    int IMAGE_WIDTH = 40;
    int IMAGE_HEIGHT = 40;
    int RELATIVE_X0 = BAR_START + BAR_LENGTH + 60;
    int RELATIVE_Y0 = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT + ((BOTTOM_BAR_HEIGHT-IMAGE_HEIGHT)/2);
    int GAP_BTW_IMAGES = 120;
    // draw resource pics
    // scrap metal
    SDL_Surface* image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scrap_metal = SDL_CreateTextureFromSurface(renderer, image);
    if (scrap_metal == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect scrap_metal_rect = { RELATIVE_X0, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, scrap_metal, NULL, &scrap_metal_rect, 0, NULL, SDL_FLIP_NONE);
    // rags
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* rags = SDL_CreateTextureFromSurface(renderer, image);
    if (rags == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect rags_rect = { RELATIVE_X0 + GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, rags, NULL, &rags_rect, 0, NULL, SDL_FLIP_NONE);
    // oil
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* oil = SDL_CreateTextureFromSurface(renderer, image);
    if (oil == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect oil_rect = { RELATIVE_X0 + 2*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, oil, NULL, &oil_rect, 0, NULL, SDL_FLIP_NONE);
    // power sources
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* power_source = SDL_CreateTextureFromSurface(renderer, image);
    if (power_source == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect power_source_rect = { RELATIVE_X0 + 3*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, power_source, NULL, &power_source_rect, 0, NULL, SDL_FLIP_NONE);
    // wire
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* wire = SDL_CreateTextureFromSurface(renderer, image);
    if (wire == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect wire_rect = { RELATIVE_X0 + 4*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, wire, NULL, &wire_rect, 0, NULL, SDL_FLIP_NONE);
    // nuclear waste
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* nuclear_waste = SDL_CreateTextureFromSurface(renderer, image);
    if (nuclear_waste == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect nuclear_waste_rect = { RELATIVE_X0 + 5*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, nuclear_waste, NULL, &nuclear_waste_rect, 0, NULL, SDL_FLIP_NONE);
    // write quantity
    // scrap metal

    // rags

    // oil

    // power sources

    // wire

    // nuclear waste

}

void drawBattleUI(const char* action1, const char* action2, const char* action3, const char* action4) {
    int RELATIVE_X0 = 100;
    int RELATIVE_Y0 = 100;
    int ACTION_BOX_WIDTH = 250;
    int ACTION_BOX_HEIGHT = 30;
    int LEFT_BORDER = 25;
    int VERTICAL_SPACING = 20;
    int PREV_BOX_HEIGHT = ACTION_BOX_HEIGHT + VERTICAL_SPACING;
    int BACKGROUND_WIDTH = 2*LEFT_BORDER + ACTION_BOX_WIDTH;
    int BACKGROUND_HEIGHT = VERTICAL_SPACING + 4*PREV_BOX_HEIGHT;

    // CURRENT COLORS ARE JUST PLACEHOLDERS -- CAN BE CHANGED
    // background rectangle
    boxRGBA(renderer, RELATIVE_X0, RELATIVE_Y0, RELATIVE_X0 + BACKGROUND_WIDTH, RELATIVE_Y0 + BACKGROUND_HEIGHT, 255, 210, 210, 255);
    // action backgrounds
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    // action labels
    drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 0, 0, 0);
    drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 0, 0, 0);
    drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 0, 0, 0);
    // action text
    drawText(action1, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action2, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action3, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action4, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
}

void window_update(const bool world) {
    if (world) {
        // Draw line for bottom bar
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar();
        drawInventory();
        SDL_RenderPresent(renderer);
    }
    else {
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar();
        drawInventory();
        /** draw battle UI -- currently commented out since this is likely not where it would be called
        // you can un-comment it just to see what it will look like (it shows up in battle mode when called here)
        drawBattleUI("Action one", "Action two", "Action three", "Action four");
        **/
        SDL_RenderPresent(renderer);
    }
}