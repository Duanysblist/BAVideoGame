#ifndef BIONIC_APOCALYPSE_CONSTANTS_H
#define BIONIC_APOCALYPSE_CONSTANTS_H

// Maximum player health
const int MAX_HEALTH = 100;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;
const int BOTTOM_BAR_HEIGHT = 100;
// Added by Daniel
const int SCREEN_BPP = 32;

//Player dimension constants
const int PLAYER_WIDTH = 80;
const int PLAYER_HEIGHT = 80;

//Enemy dimension constants
const int ENEMY_WIDTH = 80;
const int ENEMY_HEIGHT = 80;
const int ENEMY_SPEED = 5;

// Screen Directions
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;

enum GameStates {
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_CITY_BLOCK_1,
    STATE_CITY_BLOCK_2,
    STATE_CITY_BLOCK_3,
    STATE_CITY_BLOCK_4,
    STATE_BOSS_TOWER,
    STATE_EXIT,
};

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

const int OBSTACLE_WIDTH = 80;
const int OBSTACLE_HEIGHT = 70;

#endif