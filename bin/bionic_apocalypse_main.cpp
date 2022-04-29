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

    CollisionDetector collisionDetector;
    
    Renderer renderer;

    renderer.window_startup();

    Enemy badGuy;
    badGuy.setHealth(50);
    badGuy.setPosX(500);
    badGuy.setPosY(500);

    Player player;
    player.setPlayerScreenPosition(100, 300);

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

    int layout_0_0 [10][18]= 
      { {ICBR, DFW, DFW, ICBL, PW, PW, ICBR, DFW, DFW, ICBL, PW, ICBR, DFW, DFW, ICBL, PW, PW, PW}, 
        {RFW, KEY_POWER, 0, LFW, PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, LFW, PW, PW, PW},
        {RFW, 0, 0, LFW, PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, LFW, PW, PW, PW},
        {RFW, 0, 0, LFW, PW, PW, RFW, 0, 0, OCBL, DFW, OCBR, 0, 0, OCBL, DFW, DFW, DFW},
        {RFW, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, OCBL, DFW, DFW, OCBR, 0, 0, OCTL, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, LFW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, LFW, PW, PW, PW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, ICTR, UFW, UFW, ICTL, PW, PW, PW} 
    };
    map[0][0].setSceneLayout(layout_0_0);

    int layout_1_0 [10][18]= 
      { {ICBR, DFW, DFW, ICDB, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL},
        {RFW, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, TSVW, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0},
        {RFW, 0, 0, TSVW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0},
        {RFW, 0, 0, TSVW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0},
        {RFW, 0, 0, TSVW, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, OCTL},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, UFW, ICTL} 
    };
    map[1][0].setSceneLayout(layout_1_0);

    int layout_2_0 [10][18]= 
      { {PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, OCBR, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW}, 
        {PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {ICBR, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL, UFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL, UFW, UFW, ICTL, PW},
        {RFW, 0, 0, 0, 0, 0, 0, OCTL, UFW, OCTR, 0, 0, 0, LFW, PW, PW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, OCBL, DFW, OCBR, 0, 0, 0, LFW, PW, PW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW, PW, PW} 
    };
    map[2][0].setSceneLayout(layout_2_0);

    int layout_3_0 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, OCBL, DFW, ICBL, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, ICBR, DFW, DFW, OCBR, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, OCTL, UFW, ICTL}, 
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW, PW, PW} 
    };
    map[3][0].setSceneLayout(layout_3_0);

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

    int layout_7_0 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW},
        {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}
    };
    map[7][0].setSceneLayout(layout_7_0);

    int layout_0_1 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW},
        {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}
    };
    map[0][1].setSceneLayout(layout_0_1);

    int layout_1_1 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, LFW},
        {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[1][1].setSceneLayout(layout_1_1);

    int layout_2_1 [10][18]= 
      { {DFW, DFW, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW},
        {OCTR, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, OCBL, ICBL, PW, PW, PW, RFW, 0, 0, 0, 0, 0, OCBL},
        {ICTR, OCTR, 0, 0, 0, 0, 0, LFW, PW, ICBR, DFW, OCBR, 0, 0, 0, 0, 0, 0},
        {PW, ICTR, OCTR, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
        {PW, PW, ICTR, OCTR, 0, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, OCTL},
        {PW, PW, PW, ICTR, OCTR, 0, 0, LFW, PW, RFW, 0, 0, OCTL, UFW, UFW, UFW, UFW, ICTL} 
    };
    map[2][1].setSceneLayout(layout_2_1);

    int layout_3_1 [10][18]= 
      { {PW, ICBR, DFW, DFW, OCBR, 0, 0, LFW, PW, RFW, 0, 0, LFW, PW, ICBR, DFW, DFW, ICBL}, 
        {ICBR, OCBR, 0, 0, 0, 0, 0, OCBL, DFW, OCBR, 0, 0, LFW, PW, RFW, 0, 0, OCBL},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, 0},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, 0},
        {RFW, 0, 0, OCTL, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, ICTL, PW, RFW, 0, 0, OCTL},
        {RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, LFW},
        {RFW, 0, 0, OCBL, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, OCBR, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL} 
    };
    map[3][1].setSceneLayout(layout_3_1);

    int layout_4_1 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, LFW, PW, PW, PW, ICBR, OCBR, 0, 0, OCTL, UFW, OCTR, 0, 0, OCBL},
        {0, 0, 0, 0, LFW, PW, PW, ICBR, OCBR, 0, 0, 0, LFW, PW, RFW, 0, 0, 0},
        {OCTR, 0, 0, 0, LFW, PW, ICBR, OCBR, 0, 0, 0, 0, LFW, PW, RFW, 0, 0, 0},
        {RFW, 0, 0, 0, OCBL, DFW, OCBR, 0, 0, 0, 0, 0, LFW, PW, ICTR, UFW, UFW, UFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW},
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW, PW, PW, PW} 
    };
    map[4][1].setSceneLayout(layout_4_1);

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
    map[5][1].setSceneLayout(layout_5_1);

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

    int layout_7_1 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {RFW, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, OCTL, UFW, UFW},
        {0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, ROCK, 0, 0, 0, 0, LFW, PW, PW},
        {0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, LFW, PW, PW},
        {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW},
        {RFW, ROCK, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {RFW, ROCK, ROCK, ROCK, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW} 
    };
    map[7][1].setSceneLayout(layout_7_1);      

    int layout_0_2 [10][18]= 
      { {PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, LFW},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW}
    };
    map[0][2].setSceneLayout(layout_0_2);    

    int layout_1_2 [10][18]= 
      { {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {UFW, OCTR, 0, 0, 0, 0, 0, 0, OCTL, OCTR, 0, 0, 0, 0, 0, OCTL, UFW, UFW},
        {ICBR, OCBR, ROCK, ROCK, ROCK, ROCK, ROCK, ROCK, OCBL, OCBR, ROCK, ROCK, ROCK, ROCK, ROCK, LFW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {ICTR, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL}, 
        {PW, PW, PW, PW, ICTL, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[1][2].setSceneLayout(layout_1_2);    

    int layout_2_2 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, ICBR, OCBR, 0, 0, 0, OCBL, ICBL, ICBR, DFW, DFW, ICBL, PW}, 
        {PW, PW, PW, PW, PW, ICBR, OCBR, 0, 0, 0, 0, 0, LFW, RFW, 0, 0, LFW, PW},
        {PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW, RFW, 0, 0, LFW, PW},
        {PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW, RFW, 0, 0, LFW, PW},
        {PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW, RFW, 0, 0, LFW, PW},
        {DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, OCBL, OCBR, 0, 0, LFW, PW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW},
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}
    };
    map[2][2].setSceneLayout(layout_2_2);    

    int layout_3_2 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW},
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, ICBR, OCBR, 0, 0, 0, 0, 0, 0, LFW},
        {OCTR, 0, 0, 0, 0, OCBL, ICBL, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW},
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, OCTL, UFW, UFW, ICTL},
        {RFW, 0, 0, 0, 0, 0, OCBL, DFW, DFW, OCBR, 0, 0, 0, 0, LFW, PW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL, ICTL, PW, PW, PW},
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW},
        {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, OCTL, UFW, ICTL, PW, PW, PW, PW}
    };
    map[3][2].setSceneLayout(layout_3_2);    

    int layout_5_2 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, ICBR, DFW, DFW, OCBR, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, LFW, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, LFW, 0, 0, 0, 0, 0, ROCK, ROCK, OCBL, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {PW, PW, PW, LFW, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, PW, LFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, PW, LFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}
    };
    map[5][2].setSceneLayout(layout_5_2);    

    int layout_6_2 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, LFW}, 
        {RFW, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, ROCK, LFW}, 
        {RFW, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, 0, TSHW, TSHW, TSHW, ROCK, 0, 0, OCBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, ROCK, 0, 0, ROCK, OCTR, UFW, UFW}
    };
    map[6][2].setSceneLayout(layout_6_2);    

    int layout_7_2 [10][18]= 
      { {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, ROCK, 0, 0, ROCK, OCBL, DFW, ICBL}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL},
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}
    };
    map[7][2].setSceneLayout(layout_7_2);    

    int layout_0_3 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL}, 
        {OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL}, 
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[0][3].setSceneLayout(layout_0_3);    

    int layout_1_3 [10][18]= 
      { {DFW, DFW, DFW, ICBL, PW, PW, PW, RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {OCTR, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[1][3].setSceneLayout(layout_1_3);    

    int layout_2_3 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, TSVW, 0, 0, OCBL, DFW, DFW, DFW, DFW, OCBR, 0, 0, TSVW, 0, 0, OCBL}, 
        {RFW, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0}, 
        {RFW, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0}, 
        {RFW, 0, 0, ROCK, TSHW, TSHW, TSHW, TSHW, TSHW, ROCK, 0, 0, 0, 0, ROCK, ROCK, ROCK, OCTL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[2][3].setSceneLayout(layout_2_3);    

    int layout_3_3 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {ICBR, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, TSHW, TSHW, TSHW, TSHW, TSHW, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, OCTL, ICTL}
    };
    map[3][3].setSceneLayout(layout_3_3);    

    int layout_4_3 [10][18]= 
      { {PW, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, ICBL}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {DFW, DFW, DFW, ICBL, PW, PW, RFW, 0, 0, OCTL, UFW, UFW, UFW, UFW, OCTR, 0, 0, LFW}, 
        {0, 0, 0, OCBL, DFW, DFW, OCBR, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, LFW}, 
        {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, OCBR, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, OCTL, ICTL}
    };
    map[4][3].setSceneLayout(layout_4_3);    

    int layout_5_3 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, ROCK, ROCK, 0, 0, 0, OCTL, DFW, DFW, DFW, OCTR, 0, 0, 0, ROCK, LFW}, 
        {RFW, 0, 0, ROCK, 0, 0, 0, LFW, PW, PW, PW, RFW, ROCK, ROCK, 0, 0, ROCK, LFW}, 
        {OCBR, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, LFW}, 
        {0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, LFW}, 
        {OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[5][3].setSceneLayout(layout_5_3);    

    int layout_6_3 [10][18]= 
      { {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {OCBR, 0, 0, 0, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
        {0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {UFW, UFW, UFW, UFW, ICTL, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}
    };
    map[6][3].setSceneLayout(layout_6_3);    

    int layout_7_3 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICDB, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, ROCK, ROCK, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, TSHW, TSHW, TSHW, TSHW, 0, 0, 0, ROCK, TSVW, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {OCBR, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, ROCK, 0, 0, 0}, 
        {0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0}, 
        {UFW, UFW, UFW, ICDT, UFW, UFW, UFW, UFW, ICDT, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}
    };
    map[7][3].setSceneLayout(layout_7_3);    

    int layout_0_4 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, ICBL, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, OCBL, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, OCTL, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, ICTL, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
    };
    map[0][4].setSceneLayout(layout_0_4);    

    int layout_1_4 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, ICBL, PW, PW, PW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
        {ICTR, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}
    };
    map[1][4].setSceneLayout(layout_1_4);    

    int layout_2_4 [10][18]= 
      { {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
        {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
        {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
        {DFW, DFW, OCBR, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW, PW}, 
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {UFW, UFW, OCTR, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTR}, 
        {PW, PW, RFW, 0, 0, LFW, PW, ICTR, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, ICTL}, 
    };
    map[2][4].setSceneLayout(layout_2_4);    

    int layout_3_4 [10][18]= 
      { {PW, PW, RFW, 0, 0, LFW, PW, RFW, ICBR, DFW, OCBR, 0, 0, OCBL, DFW, DFW, DFW, ICBL}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, ICTR, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, ICTL}, 
    };
    map[3][4].setSceneLayout(layout_3_4);    

    int layout_4_4 [10][18]= 
      { {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, OCBL, DFW, DFW, DFW, DFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, ICBL, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
        {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
        {PW, PW, RFW, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {PW, PW, ICTR, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
    };
    map[4][4].setSceneLayout(layout_4_4);    

    int layout_5_4 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, LFW, 0, 0, 0, 0, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, LFW, 0, 0, 0, 0, RFW, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, OCBL, DFW, 0, 0, DFW, OCBR, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
    };
    map[5][4].setSceneLayout(layout_5_4);    

    int layout_6_4 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
        {RFW, ROCK, ROCK, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, OCTL, UFW, OCTR, 0, 0}, 
        {RFW, 0, 0, ROCK, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, LFW, PW, RFW, 0, 0}, 
        {RFW, ROCK, ROCK, ROCK, ROCK, 0, 0, 0, 0, ROCK, 0, 0, ROCK, OCBL, DFW, OCBR, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    };
    map[6][4].setSceneLayout(layout_6_4);    

    int layout_7_4 [10][18]= 
      { {OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, OCTL, UFW, OCTR, 0, 0, 0, ROCK, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, OCTL, ICTL, PW, ICTR, OCTR, 0, 0, 0, ROCK, ROCK, 0}, 
        {0, 0, OCTL, OCTR, 0, 0, OCTL, ICTL, PW, PW, PW, ICTR, OCTR, 0, 0, ROCK, 0, 0}, 
        {0, 0, OCBL, OCBR, 0, 0, LFW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, OCBL, ICBL, PW, PW, PW, ICBR, OCBR, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0}, 
        {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
    };
    map[7][4].setSceneLayout(layout_7_4);    

    int layout_0_5 [10][18]= 
      { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
        {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, OCTL, UFW, UFW, UFW, ICTL}, 
    };
    map[0][5].setSceneLayout(layout_0_5);    

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
                        help = !help;
                    }
                }

                // User releases a key
                if (e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_w) {
                        moveUp = false;
                        //std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        moveDown = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_d) {
                        moveRight = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_a) {
                        moveLeft = false;
                        // std::cout << player.getPlayerScreenPositionX() << ", " << player.getPlayerScreenPositionY() << "\n";
                        // std::cout << "Hitting Player: " << badGuy.playerCollisionCheck(player) << "\n";
                    }
                    if (e.key.keysym.sym == SDLK_e) {
                        interacting = false;
                    }
                }
            }

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
            moveUp = moveDown = moveLeft = moveRight = false;
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
                    if (e.key.keysym.sym == SDLK_q) {
                        running = false;
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_h) {
                        help = !help;
                    }
                }
                // User releases a key
                if (e.type == SDL_KEYUP) {
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
        renderer.window_update(player, worldState, currentScene);
        renderer.drawEnemy(badGuy.getX(), badGuy.getY());
        if (help) {
            renderer.drawHelpScreen();
        }

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