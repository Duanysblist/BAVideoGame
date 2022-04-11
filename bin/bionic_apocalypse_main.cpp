#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_battlelogic.h"
#include "bionic_apocalypse_constants.h"
#include "Scene.h"

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
    badGuy.setPosY(500);

    Player player;

    bool worldState = true; //true is world, false is battle

    // Setting up a 4x4 matrix for the map system
    int counter = 0;
    Scene map[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            map[i][j].setSceneID(counter);
            map[i][j].setSceneCategoryID(j);
            counter++;
        }
    }
      
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
                        // std::cout << "battle is pressed" << std::endl;; 
                        worldState = false;   
                    }
                    if (e.key.keysym.sym == SDLK_2) {
                        setAttackingTrue(player);
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
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        MOVE_DOWN = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_d) {
                        MOVE_RIGHT = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_a) {
                        MOVE_LEFT = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_e) {
                        INTERACTING = false;
                    }
                }
            }

            if (MOVE_UP) {
                player.playerMoveUp(); 
            }
            if (MOVE_DOWN) {
                player.playerMoveDown();
            }
            if (MOVE_LEFT) {
                player.playerMoveLeft();
            }
            if (MOVE_RIGHT) {
                player.playerMoveRight();
            }

            std::vector<int> currentVec = player.getPlayerMapPosition();
            int x = currentVec.at(0);
            int y = currentVec.at(1);
            Scene currentScene = map[x][y];

            switch(player.checkIfPlayerIsAtScreenBoundary()) {
                case 0:
                    // The player is not at the edge of the screen or there is no screen to move to in that direction
                    break;
                case 1:
                    // Move to above screen
                    // Don't change x value; y value turns from 0 to SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT
                    // setPlayerScreenPosition(sameX, newY)
                    // player.setPlayerMapPosition()
                    currentScene = map[x-1][y];
                    currentVec.at(0) = x - 1;
                    player.setPlayerMapPosition(currentVec);
                    player.setPlayerScreenPosition(player.getPlayerScreenPositionX(), SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT);
                    break;
                case 2:
                    // Move to right screen
                    // Don't change y value; x value goes from SCREEN_WIDTH - PLAYER_WIDTH to 0
                    // setPlayerScreenPosition(newX, sameY)
                    // player.setPlayerMapPosition()
                    currentScene = map[x][y + 1];
                    currentVec.at(1) = y + 1;
                    player.setPlayerMapPosition(currentVec);
                    player.setPlayerScreenPosition(0, player.getPlayerScreenPositionY());
                    break;
                case 3:
                    // Move to below screen
                    // Don't change x value; y value turns from SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT to 0
                    // setPlayerScreenPosition(sameX, newY)
                    // player.setPlayerMapPosition()
                    currentScene = map[x + 1][y];
                    currentVec.at(0) = x + 1;
                    player.setPlayerMapPosition(currentVec);
                    player.setPlayerScreenPosition(player.getPlayerScreenPositionX(), 0);
                    break;
                case 4:
                    // Move to left screen
                    // Don't change y value; x value goes fromo 0 to SCREEN_WIDTH - PLAYER_WIDTH
                    // setPlayerScreenPosition(newX, sameY)
                    // player.setPlayerMapPosition()
                    currentScene = map[x][y - 1];
                    currentVec.at(1) = y - 1;
                    player.setPlayerMapPosition(currentVec);
                    player.setPlayerScreenPosition(SCREEN_WIDTH - PLAYER_WIDTH, player.getPlayerScreenPositionY());
                    break;
            }
            
            
        }
        else {
            if(battling == false) {
                startNewBattle(badGuy);
                battling = true;
            }
            //renderer.drawEnemy(badGuy);
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_1) {
                        setAttackingTrue(player);
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
        renderer.drawPlayer(player, worldState);
        badGuy.update(&renderer);
        renderer.window_update(player, worldState);

        SDL_Delay(17);
	}

    return 0;
}