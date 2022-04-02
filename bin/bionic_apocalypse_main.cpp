#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_battlelogic.h"
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
    bool battling = false;
    SDL_Event e;
    
    Renderer renderer;

    renderer.window_startup();

    Enemy badGuy;
    badGuy.setHealth(50);
    badGuy.setPosX(500);
    badGuy.setPosY(0);

    bool worldState = true; //true is world, false is battle
      
	while (running) {
        //check if gamestate is in world
        if(worldState) { 
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
                        std::cout << "battle is pressed" << std::endl;; 
                        worldState = false;   
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
        }
        else {
            if(battling == false) {
                startNewBattle(badGuy);
                battling = true;
            }
            renderer.drawEnemy(badGuy);
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_1) {
                        setAttackingTrue();
                    }
                }

                // User releases a key
                if (e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_1) {
                        
                    }
                }
            }
            if(getStatus() == false) {
                worldState = true;
                battling = false;
            }
        }

        renderer.window_clear();
        renderer.drawPlayer(worldState);
        renderer.window_update(worldState);

        SDL_Delay(17);
	}

    return 0;
}