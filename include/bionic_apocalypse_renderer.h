
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
        SDL_Rect player_rect; 
        SDL_Rect enemy_rect = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
        TTF_Font* font;
        SDL_Texture* texture;
        SDL_Color color = { 255, 255, 255 };

        // health bar attributes
        const int BAR_LENGTH = 200;
        const int BAR_START = 30;

        // error message methods
        void csci437_error(const std::string& msg) const;
        void csci437_img_error(const std::string& msg) const;
        void csci437_ttf_error(const std::string& msg) const;

        

    public:
    // helper method
        void drawText(const char* words, const int dst_x, const int dst_y, const int r, const int g, const int b);
        void drawHealthBar(const Player player);
        void drawInventory(const Player player);
        void drawKeyInventory(const Player player);

        // window methods
        void window_startup();
        void window_clear();
        void window_update(const Player &player, const bool &world);

        void drawPlayer(const Player player, const bool world);
        void drawEnemy(const int posX, const int posY);
        void drawObstacles();

        void drawBattleUI(const char* action1, const char* action2, const char* action3, const char* action4);
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        bool checkPlayerEnemyCollision();
};

#endif
