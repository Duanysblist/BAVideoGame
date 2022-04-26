#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_battlelogic.h"
#include "bionic_apocalypse_constants.h"
#include "Scene.h"
#include "CollisionDetector.h"

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
    bool help;
    SDL_Event e;

    CollisionDetector collisionDetector;
    
    Renderer renderer;

    renderer.window_startup();

    Enemy badGuy;
    badGuy.setHealth(50);
    badGuy.setPosX(500);
    badGuy.setPosY(500);

    Player player;

    bool worldState = true; //true is world, false is battle
    Battle curBattle;


    // Setting up a MAP_ROWSxMAP_COLUMNS matrix for the map system
    int counter = 0;
    Scene map[MAP_ROWS][MAP_COLUMNS];

    // set scene zone information
    // 0 - in the tutorial zone
    // 1 - in the power source zone (blue)
    // 2 - in the wires zone (red)
    // 3 - in the nuclear waste zone (pink)
    // 4 - outside the lab
    map[0][0].setSceneZone(1);
    map[0][1].setSceneZone(1);
    map[0][2].setSceneZone(1);
    map[0][3].setSceneZone(1);
    map[0][4].setSceneZone(1);
    map[0][5].setSceneZone(2);
    map[1][0].setSceneZone(1);
    map[1][1].setSceneZone(1);
    map[1][2].setSceneZone(1);
    map[1][3].setSceneZone(1);
    map[1][4].setSceneZone(2);
    map[1][5].setSceneZone(2);
    map[2][0].setSceneZone(1);
    map[2][1].setSceneZone(1);
    map[2][2].setSceneZone(1);
    map[2][3].setSceneZone(2);
    map[2][4].setSceneZone(2);
    map[2][5].setSceneZone(2);
    map[3][0].setSceneZone(0);
    map[3][1].setSceneZone(1);
    map[3][2].setSceneZone(1);
    map[3][3].setSceneZone(2);
    map[3][4].setSceneZone(2);
    map[3][5].setSceneZone(2);
    map[4][0].setSceneZone(0);
    map[4][1].setSceneZone(0);
    map[4][2].setSceneZone(4);
    map[4][3].setSceneZone(2);
    map[4][4].setSceneZone(2);
    map[4][5].setSceneZone(2);
    map[5][0].setSceneZone(0);
    map[5][1].setSceneZone(0);
    map[5][2].setSceneZone(3);
    map[5][3].setSceneZone(3);
    map[5][4].setSceneZone(2);
    map[5][5].setSceneZone(3);
    map[6][0].setSceneZone(0);
    map[6][1].setSceneZone(0);
    map[6][2].setSceneZone(3);
    map[6][3].setSceneZone(3);
    map[6][4].setSceneZone(3);
    map[6][5].setSceneZone(3);
    map[7][0].setSceneZone(3);
    map[7][1].setSceneZone(3);
    map[7][2].setSceneZone(3);
    map[7][3].setSceneZone(3);
    map[7][4].setSceneZone(3);
    map[7][5].setSceneZone(3);

    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){
            map[i][j].setSceneID(counter);
            map[i][j].setSceneCategoryID(j);
            map[i][j].createSceneLayout(10, 18);
            counter++;
        }
    }
    
    int layout_6_0 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICDB, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, TSHW, TSHW, TSHW, TSHW, TSHW, ICDL},
        {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, CROWBAR, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICDT, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL} 
    };

    map[6][0].setSceneLayout(layout_6_0);

    int layout_6_1 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW}, 
        {DFW, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW},
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW},
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW},
        {UFW, OCTR, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW},
        {PW, RFW, 0, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, LFW, PW, PW, PW, PW, PW},
        {PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW},
        {PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW},
        {PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW},
        {PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW, PW, PW, PW} 
    };

    map[6][1].setSceneLayout(layout_6_1);

    int layout_5_1 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, METAL, 0, LFW},
        {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {PW, PW, PW, PW, PW, PW, PW, ICTR, UFW, UFW, 0, 0, UFW, UFW, UFW, UFW, UFW, ICTL} 
    };

        map[6][1].setSceneLayout(layout_6_1);

    int layout_4_0 [10][18]= 
      { {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, ROCK, ROCK, ROCK, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, ROCK, ROCK, 0, 0, 0, LFW, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW},
        {RFW, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL} 
    };

    map[4][0].setSceneLayout(layout_4_0);

    int layout_5_0 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, RFW, 0, 0, DFW, ICBL, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, ICBR, DFW, DFW, OCBR, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW},
        {PW, PW, ICBR, OCBR, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW},
        {PW, ICBR, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {ICBR, OCBR, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL, UFW, UFW},
        {RFW, 0, 0, 0, 0, ROCK, 0, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, LFW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW},
        {RFW, POWER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW},
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW} 
    };

    map[5][0].setSceneLayout(layout_5_0);

    int cur_time = SDL_GetTicks();
      
	while (running) {

        // get delta t
        unsigned int dt = SDL_GetTicks() - cur_time;
        cur_time = SDL_GetTicks();

        // get player world position
        std::vector<int> currentVec = player.getPlayerMapPosition();
        int x = currentVec.at(0);
        int y = currentVec.at(1);
        Scene currentScene = map[x][y];

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
                        //removed  
                    }
                    if (e.key.keysym.sym == SDLK_2) {
                        //removed
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
                    if (e.key.keysym.sym == SDLK_h) {
                        help = !help;
                    }
                }

                // User releases a key
                if (e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_w) {
                        MOVE_UP = false;
                        //std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
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
                player.playerMoveUp(dt); 
            }
            if (MOVE_DOWN) {
                player.playerMoveDown(dt);
            }
            if (MOVE_LEFT) {
                player.playerMoveLeft(dt);
            }
            if (MOVE_RIGHT) {
                player.playerMoveRight(dt);
            }

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
            MOVE_UP = MOVE_DOWN = MOVE_LEFT = MOVE_RIGHT = false;
            if(battling == false) {
                curBattle.startNewBattle(badGuy);
                battling = true;
            }
            //renderer.drawEnemy(badGuy);
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_1) {
                        curBattle.setAttackingTrue(player, 1);
                    }
                    
                    if (e.key.keysym.sym == SDLK_q) {
                        running = false;
                        break;
                    }
                }
                /**
                // User releases a key
                if (e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_1) {
                        
                    }
                }**/
            }
            if(curBattle.getStatus() == false) {
                worldState = true;
                battling = false;
            }
        }

        renderer.window_clear();

        collisionDetector.playerResourceCollision(player, currentScene);

        badGuy.update(dt);
        
        if(collisionDetector.playerEnemyCollision(player, badGuy)) {
            worldState = false;
        }
        renderer.window_update(player, worldState, currentScene, help);
        renderer.drawEnemy(badGuy.getX(), badGuy.getY());

        std::vector<int> a = player.getPlayerMapPosition();
        int int_positionx = a.at(0);
        int int_positiony = a.at(1);
        std::string positionx = std::to_string(int_positionx);
        std::string positiony = std::to_string(int_positiony);
        std::string position = positionx + positiony;
        char const *p_char = position.c_str();
        renderer.drawText(p_char, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255);

        renderer.renderer_present();
	}

    return 0;
}