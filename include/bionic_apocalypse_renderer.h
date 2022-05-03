
#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

#include <string>
#include "bionic_apocalypse_constants.h"
#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include <array>

class Renderer {
    private:
        //Window and image variables
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* image;
        SDL_Rect player_rect; 
        SDL_Rect cutscene_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect enemy_rect = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
        TTF_Font* font;
        SDL_Texture* texture;
        SDL_Color color = { 255, 255, 255 };

        // health bar attributes
        const int BAR_LENGTH = 180;
        const int BAR_START = 30;

        // error message methods
        void csci437_error(const std::string& msg) const;
        void csci437_img_error(const std::string& msg) const;
        void csci437_ttf_error(const std::string& msg) const;  

        // bottom bar methods
        void drawBottomBar(const Player &player);
        void drawHealthBar(const Player &player);
        void drawInventory(const Player &player);
        void drawKeyInventory(const Player &player); 

        // draw resources and obstacles
        void drawScene(const Scene &scene);  

        // write out "Press h for help" in the top right of the screen
        void drawHelpMessage(); 

    public:
        void drawText(const char* words, const int dst_x, const int dst_y, const int r, const int g, const int b);

        void drawHelpScreen();

        // window methods
        void window_startup();
        void window_clear();
        void window_update(const Player &player, const bool &world, Scene &scene);

        // display a cutscene
        void cutscene(const int num);

        void drawPlayer(const Player &player, const bool &world);
        void drawEnemy(const Enemy &enemy, const bool &gameState);

        void drawBattleUI(const Player &player);
        void drawBattleMessages(const std::string &message, const int &damage);

        void renderer_present();
};

#endif
