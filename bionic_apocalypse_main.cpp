#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_player.cpp"
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_enemy.cpp"

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



int main(int argc, char** argv) {

    //Initialize helpful variables to use
    bool MOVE_UP = false;
    bool MOVE_DOWN = false;
    bool MOVE_RIGHT = false;
    bool MOVE_LEFT = false;
    bool INTERACTING = false;

	bool running = false;
    SDL_Event e;

    Enemy badGuy;

    std::cout << getResource();

    badGuy.setHealth(50);
    std::cout << badGuy.getHealth();

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
                    //setAttackingTrue();
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
                }
                if (e.key.keysym.sym == SDLK_s) {
                    MOVE_DOWN = false;
                }
                if (e.key.keysym.sym == SDLK_d) {
                    MOVE_RIGHT = false;
                }
                if (e.key.keysym.sym == SDLK_a) {
                    MOVE_LEFT = false;
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

    return 0;
}