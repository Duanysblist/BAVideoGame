
#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

#include <string>
#include "bionic_apocalypse_constants.h"
#include "bionic_apocalypse_player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

class Renderer {
    private:
        //Window and image variables
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* image;
        SDL_Texture* player_texture;
        SDL_Texture* enemy;
        SDL_Rect player_rect; 
        SDL_Rect enemy_rect = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
        TTF_Font* font;
        SDL_Texture* texture;
        SDL_Color color = { 255, 255, 255 };
        int BAR_LENGTH = 200;
        int BAR_START = 30;

    public:
        void csci437_error(const std::string& msg) const;

        void csci437_img_error(const std::string& msg) const;

        void csci437_ttf_error(const std::string& msg) const;

        void drawHealthBar(Player player);

        void drawText(const char* words, int dst_x, int dst_y, int r, int g, int b);

        void drawInventory(Player player);

        void drawKeyInventory(Player player);

        void window_startup();

        void window_clear();

        void window_update(Player player, const bool world);

        void drawPlayer(Player player, const bool world);

        void drawEnemy(int posX, int posY);

        void drawBattleUI(const char* action1, const char* action2, const char* action3, const char* action4);
};

#endif
