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
    bool moveUp = false;
    bool moveDown = false;
    bool moveRight = false;
    bool moveLeft = false;
    bool interacting = false;
	bool running = true;
    bool battling = false;
    bool help = false;
    SDL_Event e;

    int eCount = 0;
    bool finalCutsceneTrigger = false;
    bool hasBeenToLab = false;
    bool hasObtainedPower = false;
    bool hasObtainedFuse = false;
    bool hasObtainedWaste = false;

    int playerWalkCycle = 0;

    CollisionDetector collisionDetector;
    
    Renderer renderer;

    renderer.window_startup();

    // enemy being used during development of the game
    Enemy badGuy;
    badGuy.setType(0);
    badGuy.setPosX(500);
    badGuy.setPosY(500);

    // initalize player, set initial position of player on the screen (bottom left)
    Player player;
    player.setPlayerScreenPosition(100, 450);

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

    // set info for each scene
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){
            map[i][j].setSceneID(counter);
            map[i][j].setSceneCategoryID(j);
            map[i][j].createSceneLayout(10, 18);
            counter++;
        }
    }

    // set scene layouts to hardcoded layouts
    map[0][0].setSceneLayout(layout_0_0);
    map[1][0].setSceneLayout(layout_1_0);
    map[2][0].setSceneLayout(layout_2_0);
    map[3][0].setSceneLayout(layout_3_0);
    map[4][0].setSceneLayout(layout_4_0);
    map[5][0].setSceneLayout(layout_5_0);
    map[6][0].setSceneLayout(layout_6_0);
    map[7][0].setSceneLayout(layout_7_0);
    map[0][1].setSceneLayout(layout_0_1);
    map[1][1].setSceneLayout(layout_1_1);
    map[2][1].setSceneLayout(layout_2_1);
    map[3][1].setSceneLayout(layout_3_1);
    map[4][1].setSceneLayout(layout_4_1);
    map[5][1].setSceneLayout(layout_5_1);
    map[6][1].setSceneLayout(layout_6_1);
    map[7][1].setSceneLayout(layout_7_1);      
    map[0][2].setSceneLayout(layout_0_2);    
    map[1][2].setSceneLayout(layout_1_2);    
    map[2][2].setSceneLayout(layout_2_2);    
    map[3][2].setSceneLayout(layout_3_2);    
    map[4][2].setSceneLayout(layout_4_2);    
    map[5][2].setSceneLayout(layout_5_2);    
    map[6][2].setSceneLayout(layout_6_2);    
    map[7][2].setSceneLayout(layout_7_2);    
    map[0][3].setSceneLayout(layout_0_3);    
    map[1][3].setSceneLayout(layout_1_3);    
    map[2][3].setSceneLayout(layout_2_3);    
    map[3][3].setSceneLayout(layout_3_3);    
    map[4][3].setSceneLayout(layout_4_3);    
    map[5][3].setSceneLayout(layout_5_3);    
    map[6][3].setSceneLayout(layout_6_3);    
    map[7][3].setSceneLayout(layout_7_3);    
    map[0][4].setSceneLayout(layout_0_4);    
    map[1][4].setSceneLayout(layout_1_4);    
    map[2][4].setSceneLayout(layout_2_4);    
    map[3][4].setSceneLayout(layout_3_4);    
    map[4][4].setSceneLayout(layout_4_4);    
    map[5][4].setSceneLayout(layout_5_4);    
    map[6][4].setSceneLayout(layout_6_4);    
    map[7][4].setSceneLayout(layout_7_4);    
    map[0][5].setSceneLayout(layout_0_5);    
    map[1][5].setSceneLayout(layout_1_5);    
    map[2][5].setSceneLayout(layout_2_5);    
    map[3][5].setSceneLayout(layout_3_5); 
    map[4][5].setSceneLayout(layout_4_5); 
    map[5][5].setSceneLayout(layout_5_5); 
    map[6][5].setSceneLayout(layout_6_5); 
    map[7][5].setSceneLayout(layout_7_5); 

    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){
            map[i][j].distributeResources();
        }
    }

    // start keeping track of time for use in player and enemy movement
    int cur_time = SDL_GetTicks();

    // set which scene the player starts in (first tutorial scene)
    std::vector<int> screenIndex{6, 0};
    player.setPlayerMapPosition(screenIndex);

    // cut scenes for player -- press e to move through them
    while (eCount < 4) {
        while (SDL_PollEvent(&e) != 0)
        {
            // User presses a key
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_e) {
                    eCount += 1;
                    SDL_Delay(100);
                }
            }
        }
        renderer.cutscene(eCount);
        renderer.renderer_present();
    }
      
    // game loop
	while (running) {

        // get delta t
        unsigned int dt = SDL_GetTicks() - cur_time;
        cur_time = SDL_GetTicks();

        // get player map location
        std::vector<int> currentVec = player.getPlayerMapPosition();
        int x = currentVec.at(0);
        int y = currentVec.at(1);
        Scene currentScene = map[x][y];

        // if the player has all of the key resources and is at the lab, stop running the game loop and play the final scene
        if (hasObtainedPower && hasObtainedFuse && hasObtainedWaste && x == 4 && y == 2) {
            running = false;
            finalCutsceneTrigger = true;
        }

        //Catalyst cutscene check
        if (!hasObtainedPower && player.getKeyResource(0) == 1) {
            hasObtainedPower = true;
            while (eCount < CUTSCENE_POWER) {
                moveDown = false;
                moveUp = false;
                moveRight = false;
                moveLeft = false;
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_e) {
                            eCount += 1;
                            SDL_Delay(100);
                        }
                    }
                }
            renderer.cutscene(eCount);
            renderer.renderer_present();
            }
        }

        //Fuse cutscene check
        if (!hasObtainedFuse && player.getKeyResource(1) == 1) {
            hasObtainedFuse = true;
            while (eCount < CUTSCENE_FUSE) {
                moveDown = false;
                moveLeft = false;
                moveRight = false;
                moveUp = false;
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_e) {
                            eCount += 1;
                            SDL_Delay(100);
                        }
                    }
                }
            renderer.cutscene(eCount);
            renderer.renderer_present();
            }
        }

        //Waste cutscene check
        if (!hasObtainedWaste && player.getKeyResource(2) == 1) {
            hasObtainedWaste = true;
            while (eCount < CUTSCENE_NUCLEAR) {
                moveDown = false;
                moveUp = false;
                moveLeft = false;
                moveRight = false;
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_e) {
                            eCount += 1;
                            SDL_Delay(100);
                        }
                    }
                }
            renderer.cutscene(eCount);
            renderer.renderer_present();
            }
        }

        //Lab cutscene check
        if (hasBeenToLab==false && x == 4 && y == 2) {
            hasBeenToLab = true;
            while (eCount < CUTSCENE_LAB) {
                moveDown = false;
                moveUp = false;
                moveLeft = false;
                moveRight = false;
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_e) {
                            eCount += 1;
                            SDL_Delay(100);
                        }
                    }
                }
            renderer.cutscene(eCount);
            renderer.renderer_present();
            }
        }

        //check if gamestate is in world
        if(worldState) { 
            //Check for input
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_q) {
                        // quit game
                        running = false;
                        break;
                    }          
                    if (e.key.keysym.sym == SDLK_w) {
                        moveUp = true;
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        moveDown = true;
                    }
                    if (e.key.keysym.sym == SDLK_d) {
                        moveRight = true;
                    }
                    if (e.key.keysym.sym == SDLK_a) {
                        moveLeft = true;
                    }
                    if (e.key.keysym.sym == SDLK_e) {
                        interacting = true;
                    }
                    if (e.key.keysym.sym == SDLK_h) {
                        // show/hide help screen
                        help = !help;
                    }
                }

                // User releases a key
                if (e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_w) {
                        moveUp = false;
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        moveDown = false;
                    }
                    if (e.key.keysym.sym == SDLK_d) {
                        moveRight = false;
                    }
                    if (e.key.keysym.sym == SDLK_a) {
                        moveLeft = false;
                    }
                    if (e.key.keysym.sym == SDLK_e) {
                        interacting = false;
                    }
                }
            }

            // store screen positions
            int prevPlayerXPos = player.getPlayerScreenPositionX();
            int prevPlayerYPos = player.getPlayerScreenPositionY();

            
            if (moveUp) {
                player.playerMoveUp(dt); 
            }
            if (moveDown) {
                player.playerMoveDown(dt);
            }
            if (moveLeft) {
                player.playerMoveLeft(dt);
            }
            if (moveRight) {
                player.playerMoveRight(dt);
            }
            if (moveUp || moveDown || moveLeft || moveRight) {
                playerWalkCycle++;
                if (playerWalkCycle >= 20) {
                    player.setWalkingAnim(!player.getWalkingAnim());
                    playerWalkCycle = 0;
                }
            }
            else {
                player.setWalkingAnim(false);
                playerWalkCycle = 0;
            }

            // check if player is hitting a wall or obstacle and limit movement if necessary
            switch(collisionDetector.playerWallCollision(player, currentScene)) {
                case 0:
                    // Player is not colliding with a wall or rock
                    break;
                case 1:
                    // Upper Left Wall Collision
                    // Send player down and to the right
                    player.setPlayerScreenPosition(prevPlayerXPos, prevPlayerYPos);
                    break;
                case 2:
                    // Upper Right Wall Collision
                    // Send player down and to the left
                    player.setPlayerScreenPosition(prevPlayerXPos, prevPlayerYPos);
                    break;
                case 3:
                    // Lower Left Wall Collision
                    // Send player up and to the right
                    player.setPlayerScreenPosition(prevPlayerXPos, prevPlayerYPos);
                    break;
                case 4:
                    // Lower Right Wall Collision
                    // Send player up and to the left
                    player.setPlayerScreenPosition(prevPlayerXPos, prevPlayerYPos);
                    break;
            }

            // check if player is moving between scenes
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
        else { // in battle mode
            // stop movement
            moveUp = moveDown = moveLeft = moveRight = false;
            // start a new battle if necessary
            if(battling == false) {
                curBattle.startNewBattle(badGuy);
                battling = true;
            }
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_q) {
                        // quit game
                        running = false;
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_h) {
                        // show/hide help screen
                        help = !help;
                    }
                }
                // User releases a key
                if (e.type == SDL_KEYUP) {
                    // battle actions
                    if (e.key.keysym.sym == SDLK_0) {
                        curBattle.setAttackingTrue(player, 0);
                    }
                    if (e.key.keysym.sym == SDLK_1) {
                        curBattle.setAttackingTrue(player, 1);
                    }
                    if (e.key.keysym.sym == SDLK_2) {
                        curBattle.setAttackingTrue(player, 2);
                    }
                    if (e.key.keysym.sym == SDLK_3) {
                        curBattle.setAttackingTrue(player, 3);
                    }
                    if (e.key.keysym.sym == SDLK_4) {
                        curBattle.setAttackingTrue(player, 4);
                    }
                    if (e.key.keysym.sym == SDLK_5) {
                        curBattle.setAttackingTrue(player, 5);
                    }
                    if (e.key.keysym.sym == SDLK_6) {
                        curBattle.setAttackingTrue(player, 6);
                    }
                    if (e.key.keysym.sym == SDLK_7) {
                        curBattle.setAttackingTrue(player, 7);
                    }
                    if (e.key.keysym.sym == SDLK_8) {
                        curBattle.setAttackingTrue(player, 8);
                    }
                    if (e.key.keysym.sym == SDLK_9) {
                        curBattle.setAttackingTrue(player, 9);
                    }
                    if (e.key.keysym.sym == SDLK_MINUS) {
                        curBattle.setAttackingTrue(player, 10);
                    }
                    if (e.key.keysym.sym == SDLK_PLUS) {
                        curBattle.setAttackingTrue(player, 11);
                    }
                }
            }
            badGuy.setHealth(curBattle.getEnemyHP());
            if(curBattle.getStatus() == false) { // leave battle
                worldState = true;
                battling = false;
                if (curBattle.getWin()){ // player won battle -- kill enemy
                    badGuy.setAlive(false);
                }
                else { // player lost battle -- reset game
                    std::vector<int> screenIndex{6, 0};
                    player.setPlayerMapPosition(screenIndex);
                    player.setPlayerScreenPosition(100, 450);
                    player.setPlayerHealth(MAX_HEALTH);
                    player.resetResources();
                }
            }
        }



        // check if player is touching a resource
        collisionDetector.playerResourceCollision(player, currentScene);

        // update enemy info
        badGuy.update(dt);
        // check if player hit enemy, switch into battle if yes
        if(collisionDetector.playerEnemyCollision(player, badGuy) && badGuy.getAlive()) {
            worldState = false;
        }

        // render everything
        renderer.window_clear();
        renderer.window_update(player, worldState, currentScene);
        renderer.drawEnemy(badGuy, worldState);
        if (help) {
            renderer.drawHelpScreen();
        }

        // display map location -- DELETE BEFORE SUBMITTING GAME - FOR DEVELOPMENT USE ONLY
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

    // display final cutscenes!
    while (finalCutsceneTrigger && eCount < CUTSCENE_END) {
            while (SDL_PollEvent(&e) != 0)
            {
                // User presses a key
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_e) {
                        eCount += 1;
                        SDL_Delay(100);
                    }
                }
            }
            renderer.cutscene(eCount);
            renderer.renderer_present();
        }

    return 0;
}
