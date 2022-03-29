#ifndef BIONIC_APOCALYPSE_CONSTANTS_H
#define BIONIC_APOCALYPSE_CONSTANTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;
const int BOTTOM_BAR_HEIGHT = 100;

//Player dimension constants
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 100;

//Enemy dimension constants
const int ENEMY_WIDTH = 100;
const int ENEMY_HEIGHT = 100;

const int defaultScreenLayout[9][16] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


#endif