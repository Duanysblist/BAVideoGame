#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_battlelogic.h"
#include "bionic_apocalypse_scene.h"
#include "bionic_apocalypse_constants.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>


#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;



int main(int argc, char *argv[]) {

    //Initialize helpful variables to use
    bool MOVE_UP = false;
    bool MOVE_DOWN = false;
    bool MOVE_RIGHT = false;
    bool MOVE_LEFT = false;
    bool INTERACTING = false;

	bool running = true;
    SDL_Event e;

    std::cout << getResource();
    
    window_startup();

    Enemy badGuy;
    badGuy.setHealth(50);
    badGuy.setPosX(500);
    badGuy.setPosY(500);
    new Enemy[] enemyList = {badGuy};
    
    Scene curScene = new Scene(0, defaultScreenLayout, {{0},{0}}, {{0},{0}}, enemyList);
      
	while (running) {

        //Check for input
        while (SDL_PollEvent(&e) != 0)
        {
            // User presses a key
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_q) {
                    running = false;
                }
                if (e.key.keysym.sym == SDLK_1) {
                    //startNewBattle(badGuy);
                    //drawEnemy(500,500);
                    //badGuy.draw();
                }
                if (e.key.keysym.sym == SDLK_2) {
                    setAttackingTrue();
                }           
                if (e.key.keysym.sym == SDLK_w) {
                    MOVE_UP = true;
                }
                if (e.key.keysym.sym == SDLK_s) {
                    MOVE_DOWN = true;
                }
                if (e.key.keysym.sym == SDLK_d) {
                    MOVE_RIGHT = true;
                }
                if (e.key.keysym.sym == SDLK_a) {
                    MOVE_LEFT = true;
                }
                if (e.key.keysym.sym == SDLK_e) {
                    INTERACTING = true;
                }
            }

            // User releases a key
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_w) {
                    MOVE_UP = false;
                    std::cout << getPlayerScreenPositionX() << ", " << getPlayerScreenPositionY() << "\n";
                }
                if (e.key.keysym.sym == SDLK_s) {
                    MOVE_DOWN = false;
                    std::cout << getPlayerScreenPositionX() << ", " << getPlayerScreenPositionY() << "\n";
                }
                if (e.key.keysym.sym == SDLK_d) {
                    MOVE_RIGHT = false;
                    std::cout << getPlayerScreenPositionX() << ", " << getPlayerScreenPositionY() << "\n";
                }
                if (e.key.keysym.sym == SDLK_a) {
                    MOVE_LEFT = false;
                    std::cout << getPlayerScreenPositionX() << ", " << getPlayerScreenPositionY() << "\n";
                }
                if (e.key.keysym.sym == SDLK_e) {
                    INTERACTING = false;
                }
            }
        }

        if (MOVE_UP) {
            playerMoveUp();
        }
        if (MOVE_DOWN) {
            playerMoveDown();
        }
        if (MOVE_LEFT) {
            playerMoveLeft();
        }
        if (MOVE_RIGHT) {
            playerMoveRight();
        }

        window_clear();
        drawPlayer();
        curScene.update();
        curScene.draw();
        window_update();

        SDL_Delay(17);
	}

    return 0;
}