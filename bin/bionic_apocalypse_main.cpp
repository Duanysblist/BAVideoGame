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

// ***********************************************************************
    int runningEnemyIDcount = 0;
    bool ranOnce = false;
    // ***********************************************************************

    //Initialize helpful variables to use
    bool moveUp = false;
    bool moveDown = false;
    bool moveRight = false;
    bool moveLeft = false;
    bool interacting = false;
	bool running = true;
    bool battling = false;
    bool help = false;
    bool map_display = false;
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

    // initialize pointer for current enemy
    Enemy *currentBattleEnemy;

    // initalize player, set initial position of player on the screen (bottom left)
    Player player;
    player.setPlayerScreenPosition(100, 450);

    bool worldState = true; //true is world, false is battle
    Battle curBattle;   // one battle object to use for all battles
    std::string curMove = ""; // empty string to use for battle messages
    int enemyDam = 0;
    int playerDam = 0;
    bool canMakeMove = true;
    bool firstMove = false;

    // Setting up a MAP_ROWSxMAP_COLUMNS matrix of scenes for the map system
    Scene map[MAP_ROWS][MAP_COLUMNS];

    // set scene zone information (used for resource generation)
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
    int sceneIDCounter = 0;
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){
            map[i][j].setSceneID(sceneIDCounter);
            map[i][j].setSceneCategoryID(j);
            // create random scene layout
            map[i][j].createSceneLayout(10, 18);
            sceneIDCounter++;
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
    map[4][2].setSceneLayout(north_unlocked);    
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

    // increase probability of resource generation for some specific scenes
    map[0][0].setResourceProbability(30);
    map[0][1].setResourceProbability(40);
    map[0][4].setResourceProbability(40);
    map[0][5].setResourceProbability(30);
    map[1][0].setResourceProbability(90);
    map[5][3].setResourceProbability(40);
    map[5][4].setResourceProbability(40);
    map[7][0].setResourceProbability(20);
    map[7][3].setResourceProbability(50);

    // randomly distribute resources in scene layouts
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){
            map[i][j].distributeResources();
        }
    }

    // start keeping track of time for use in player and enemy movement
    int cur_time = SDL_GetTicks();
    // keeping track of time for temporary messages
    int mes_time = SDL_GetTicks();

    // set which scene the player starts in (first tutorial scene)
    std::vector<int> screenIndex{6, 0};
    player.setPlayerMapPosition(screenIndex);

    int sceneNumber = 0;

    // create a list of enemies
    // the list has sublists -- each sublist represents the enemies from one scene
    std::vector<std::vector<Enemy *>> allEnemies;
    for(int a = 0; a < MAP_ROWS; a++) {
        for(int b = 0; b < MAP_COLUMNS; b++) {
            std::cout<<"Scene number: " + std::to_string(sceneNumber) << endl;
            sceneNumber++;
            std::vector<Enemy *> enemiesScene;
            for(int i = 0; i < map[a][b].getSceneRows(); i++){
                for(int j = 0; j < map[a][b].getSceneColumns(); j++){
                    int** theScene = map[a][b].getSceneLayout();
                    // Check if the ENEMY_START constant is in the scene -- means there is at least one enemy in the scene
                    if(theScene[i][j] == ENEMY_START) {
                    // If so, give the pixel position it is supposed to be in
                    int* pixPos = map[a][b].covertScenePosToPixels(i, j);
                    // Create an enemy object
                    Enemy* newEnemy = new Enemy();
                    // Set the position of the enemy in the scene
                    newEnemy->setPosX(pixPos[1]);
                    newEnemy->setPosY(pixPos[0]);
                    newEnemy->setStartLocation(pixPos[1], pixPos[0]);
                    newEnemy->setType((rand() % 3) - 1);
                    std::cout<<"EnemyID: " + std::to_string(runningEnemyIDcount) << endl;
                    // add enemy to the list
                    enemiesScene.push_back(newEnemy);
                    newEnemy->setID(runningEnemyIDcount);
                    std::cout<<"Enemy default ending location x: " + std::to_string(newEnemy->getEndLocationX());
                    int* enemyEnd;
                    switch(runningEnemyIDcount){
                        case 6:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 3);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 7:
                            enemyEnd = map[a][b].covertScenePosToPixels(4, 8);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 8:
                            enemyEnd = map[a][b].covertScenePosToPixels(5, 12);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 9:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 9);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 10:
                            enemyEnd = map[a][b].covertScenePosToPixels(2, 16);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 17:
                            enemyEnd = map[a][b].covertScenePosToPixels(4, 11);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 20:
                            enemyEnd = map[a][b].covertScenePosToPixels(2, 8);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 22:
                            enemyEnd = map[a][b].covertScenePosToPixels(4, 16);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 23:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 9);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 24:
                            enemyEnd = map[a][b].covertScenePosToPixels(7, 1);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 27:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 5);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 31:
                            enemyEnd = map[a][b].covertScenePosToPixels(5, 16);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 32:
                            enemyEnd = map[a][b].covertScenePosToPixels(7, 14);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 33:
                            enemyEnd = map[a][b].covertScenePosToPixels(1, 1);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 34:
                            enemyEnd = map[a][b].covertScenePosToPixels(1, 11);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 35:
                            enemyEnd = map[a][b].covertScenePosToPixels(5, 5);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 36:
                            enemyEnd = map[a][b].covertScenePosToPixels(5, 16);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 37:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 16);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 40:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 10);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 41:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 1);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 42:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 5);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 44:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 15);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 45:
                            enemyEnd = map[a][b].covertScenePosToPixels(2, 8);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 47:
                            enemyEnd = map[a][b].covertScenePosToPixels(8, 12);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                        case 48:
                            enemyEnd = map[a][b].covertScenePosToPixels(4, 2);
                            newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                            break;
                    }
                    // CAN HARDCODE THE DIFFERENT PATHS THAT ENEMIES NEED TO TAKE BASED UPON THEIR IDS
                        // IS THERE A SIMPLER WAY TO DO THIS?
                        // int* enemyEnd;
                        // These are the scene numbers and enemy IDs that will be moving and need to patrol
                        // Scene #7 -> [1, 1]: Enemy IDs: 6, 7, 8, 9, 10
                            // enemyEnd = map[a][b].convertScenePosToPixels(8, 3);
                            // newEnemy->setEndLocation(enemyEnd[1], enemyEnd[0]);
                        // Scene #14: Enemy IDs: 17
                        // Scene #22: Enemy IDs: 20, 22, 23
                        // Scene #23: Enemy IDs: 24
                        // Scene #30: Enemy IDs: 27
                        // Scene #33: Enemy Ids: 30, 31
                        // Scene #34: Enemy IDs: 32, 33, 34, 35, 36
                        // Scene #38: Enemy IDs: 39, 40
                        // Scene #43: Enemy IDs: 41, 43
                        // Scene #44: Enemy IDs: 44
                        // Scene #45: Enemy IDs: 46, 47
                         //if(newEnemy->getID() == 17) {
                            //newEnemy->setEndLocation(500, 600);

                            // THEN CALL UPDATE ONE ENEMIES BELOW (Line ~750)
                        //}

                    enemiesScene.push_back(newEnemy);
                    runningEnemyIDcount++;
                    // Add enemy to our array of enemies in the scene
                    
                    // increment the number of enemies
                    // enemyCounter++;
                    // std::cout << "Enemy Position :" + std::to_string(i) + ", " + std::to_string(j);
                    }
                }
            }
            allEnemies.push_back(enemiesScene);
        }
    }




    // beginning cut scenes for player -- press e to move through them
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

    // Making an array of possible enemies in the scene
    // Will never be more than 6 enemies in a single scene
    std::vector<Enemy *> enemiesInScene;
    int enemyCounter = 0;

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
        enemiesInScene = allEnemies.at(currentScene.getSceneID());

        // if the player has all of the key resources and is at the lab, stop running the game loop and play the final scene
        if (hasObtainedPower && hasObtainedFuse && hasObtainedWaste && x == 4 && y == 2) {
            running = false;
            finalCutsceneTrigger = true;
        }

        //Catalyst cutscene check (big battery)
        if (!hasObtainedPower && player.getKeyResource(0) == 1) {
            hasObtainedPower = true;
            // change lab layout to unlock wire zone
            map[4][2].setSceneLayout(east_unlocked);
            // show cutscenes
            while (eCount < CUTSCENE_POWER) {
                // stop player movement
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
            // move player back to the lab
            player.setPlayerMapPosition({4, 2});
            player.setPlayerScreenPosition(10, (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/2);
        }

        //Fuse cutscene check
        if (!hasObtainedFuse && player.getKeyResource(1) == 1) {
            hasObtainedFuse = true;
            // change lab layout to unlock nuclear zone
            map[4][2].setSceneLayout(layout_4_2);
            // show cutscenes
            while (eCount < CUTSCENE_FUSE) {
                // stop player movement
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
            // move player back to the lab
            player.setPlayerMapPosition({4, 2});
            player.setPlayerScreenPosition(10, (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/2);
        }

        //Waste cutscene check --- do NOT move player back to the lab bc then they automatically win
        if (!hasObtainedWaste && player.getKeyResource(2) == 1) {
            hasObtainedWaste = true;
            // show cutscenes
            while (eCount < CUTSCENE_NUCLEAR) {
                // stop player movement
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

        //Lab cutscene check -- play when player first goes to the lab
        if (hasBeenToLab==false && x == 4 && y == 2) {
            hasBeenToLab = true;
            while (eCount < CUTSCENE_LAB) {
                // stop player movement
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
            // move player slightly to the right so they don't flicker between the two scenes
            player.setPlayerScreenPosition(10, player.getPlayerScreenPositionY());
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
                    if (e.key.keysym.sym == SDLK_h) {
                        // show/hide help screen
                        help = !help;
                    }
                    if (e.key.keysym.sym == SDLK_m) {
                        // show/hide map
                        map_display = !map_display;
                    }
                    if (e.key.keysym.sym == SDLK_b) {
                        // use bandages to heal
                        if (player.getResource(1) > 0) {
                            player.setResource(1, -1);
                            player.changePlayerHealth(5);
                        }
                    }
                    if (e.key.keysym.sym == SDLK_t) {
                        // use tourniquet to heal
                        if (player.getResource(1) > 0 && player.getResource(1) > 4) {
                            player.setResource(1, -1);
                            player.setResource(4, -1);
                            player.changePlayerHealth(15);
                        }
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
                    // if (e.key.keysym.sym == SDLK_1) {
                    //     bool can = player.useBandage();
                    //     if (can == false) {
                    //         canMakeMove = false;
                    //         mes_time = SDL_GetTicks();
                    //     }
                    // }
                    // if (e.key.keysym.sym == SDLK_8) {
                    //     bool can = player.useTour();
                    //     if (can == false) {
                    //         canMakeMove = false;
                    //         mes_time = SDL_GetTicks();
                    //     }
                    // }
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
            // player walk cycle for animating player feet movements
            if (moveUp || moveDown || moveLeft || moveRight) {
                playerWalkCycle++;
                if (playerWalkCycle >= 20) {
                    player.setWalkingAnim(!player.getWalkingAnim());
                    playerWalkCycle = 0;
                }
            }
            else { // player is standing still so feet should be still
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
                curBattle.startNewBattle(player, *currentBattleEnemy);
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
                        bool can = curBattle.setAttackingTrue(player, 0);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_1) {
                        bool can = curBattle.setAttackingTrue(player, 1);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_2) {
                        bool can = curBattle.setAttackingTrue(player, 2);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_3) {
                        bool can = curBattle.setAttackingTrue(player, 3);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_4) {
                        bool can = curBattle.setAttackingTrue(player, 4);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_5) {
                        bool can = curBattle.setAttackingTrue(player, 5);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_6) {
                        bool can = curBattle.setAttackingTrue(player, 6);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_7) {
                        bool can = curBattle.setAttackingTrue(player, 7);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_8) {
                        bool can = curBattle.setAttackingTrue(player, 8); 
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            canMakeMove = true;
                            firstMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_9) {
                        bool can = curBattle.setAttackingTrue(player, 9);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            firstMove = true;
                            canMakeMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_MINUS) {
                        bool can = curBattle.setAttackingTrue(player, 10);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            firstMove = true;
                            canMakeMove = true;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_EQUALS) {
                        bool can = curBattle.setAttackingTrue(player, 11);
                        if (can == false){
                            canMakeMove = false;
                            mes_time = SDL_GetTicks();
                        }
                        else{
                            firstMove = true;
                            canMakeMove = true;
                        }
                    }
                }
            }
            // because the enemy here is different from the enemy object in the battle, need to update this enemy's health
            currentBattleEnemy->setHealth(curBattle.getEnemyHP());

            curBattle.checkAvailableMoves(player);

            // get info of moves and damage for battle messages
            curMove = curBattle.getCurMove();
            enemyDam = curBattle.getEnemyDamage();
            playerDam = curBattle.getPlayerDamage();

            if(curBattle.getStatus() == false) { // leave battle if it is ended
                worldState = true;
                battling = false;
                firstMove = false;
                if (curBattle.getWin()){ // player won battle -- kill enemy
                    // kill enemy here since it is a different object from the enemy object in the battle
                    currentBattleEnemy->setAlive(false);
                }
                else { // player lost battle -- reset game
                    // return the player to initial position
                    std::vector<int> screenIndex{6, 0};
                    player.setPlayerMapPosition(screenIndex);
                    player.setPlayerScreenPosition(100, 450);
                    // reset player stats
                    player.setPlayerHealth(MAX_HEALTH);
                    player.resetResources();
                    // lock up zones again
                    map[4][2].setSceneLayout(north_unlocked); 
                    // add crowbar to the map again
                    map[6][0].setSceneLayout(layout_6_0);
                    // add key resources back to the map
                    map[0][0].setSceneLayout(layout_0_0);
                    map[3][5].setSceneLayout(layout_3_5);
                    map[5][5].setSceneLayout(layout_5_5);
                    // add resources from the tutorial zone back to the map
                    map[3][0].setSceneLayout(layout_3_0);
                    map[4][0].setSceneLayout(layout_4_0);
                    map[5][0].setSceneLayout(layout_5_0);
                    map[6][0].setSceneLayout(layout_6_0);
                    map[4][1].setSceneLayout(layout_4_1);
                    map[5][1].setSceneLayout(layout_5_1);
                    map[6][1].setSceneLayout(layout_6_1);
                    // distribute resources in the map again
                    for(int i = 0; i < MAP_ROWS; i++){
                        for(int j = 0; j < MAP_COLUMNS; j++){
                            map[i][j].distributeResources();
                        }
                    }
                    // reset enemies
                    for (int i = 0; i < allEnemies.size(); i++) {
                        for (int j = 0; j < allEnemies.at(i).size(); i++) {
                            // make alive again
                            allEnemies.at(i).at(j)->setAlive(true);
                            // set health back to max
                            allEnemies.at(i).at(j)->setHealth(allEnemies.at(i).at(j)->getMaxHealth());
                        }
                    }

                }
            }
        }

        // check if player is touching a resource
        collisionDetector.playerResourceCollision(player, currentScene);


        // check if player hit enemy, switch into battle if yes
        // ***********************************************************************
        for(int a = 0; a < enemiesInScene.size(); a++) {
            // If the enemy has had it's end location changed, and you're in the world state, make the enemy path
            if(enemiesInScene.at(a)->getEndLocationX() != 900) {
                if(worldState) {
                    enemiesInScene.at(a)->update(dt);
                }
            }
          if(collisionDetector.playerEnemyCollision(player, *enemiesInScene.at(a)) && enemiesInScene.at(a)->getAlive()){
            worldState = false;
            currentBattleEnemy = enemiesInScene.at(a);
            break;
          }
        }
        // ***********************************************************************

        // render everything
        renderer.window_clear();
        renderer.window_update(player, worldState, currentScene);
        // Draw all enemies in the scene
        // ***********************************************************************

        if(worldState) {
          for(int i = 0; i < enemiesInScene.size(); i++){
            if(enemiesInScene.at(i)->getAlive()) {
                // std::cout << std::to_string(enemiesInScene.at(i)->getID());
              renderer.drawEnemy(*enemiesInScene.at(i), worldState); 
            }
          }
        } else {
          if(currentBattleEnemy->getAlive()) {
            renderer.drawEnemy(*currentBattleEnemy, worldState);
          }
        }
        // ***********************************************************************

        if(firstMove && canMakeMove) { // if a battle is going on and a move has been taken
            renderer.drawBattleMessages(curMove, enemyDam, playerDam);
        }

        if(cur_time >= (mes_time + 3000)) { //stop displaying cant make move message after 3 seconds
            canMakeMove = true;
        }

        if(canMakeMove == false){ //if move has been made that cannot be done we display message
            renderer.drawCantUseMove();
        }

        // display help screen if player pressed h
        if (help) {
            renderer.drawHelpScreen();
        }
        // display map if player pressed m
        if (map_display) {
            renderer.drawMap(player.getPlayerMapPosition());
        }

        // display map location -- DELETE BEFORE SUBMITTING GAME - FOR DEVELOPMENT USE ONLY
        // ****************************************************
        // std::vector<int> a = player.getPlayerMapPosition();
        // int int_positionx = a.at(0);
        // int int_positiony = a.at(1);
        // std::string positionx = std::to_string(int_positionx);
        // std::string positiony = std::to_string(int_positiony);
        // std::string position = positionx + positiony;
        // char const *p_char = position.c_str();
        // renderer.drawText(p_char, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255);
        // *****************************************************

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
