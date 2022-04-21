#ifndef BIONIC_APOCALYPSE_CONSTANTS_H
#define BIONIC_APOCALYPSE_CONSTANTS_H

// Maximum player health
const int MAX_HEALTH = 100;

//Screen dimension constants
const int SCREEN_WIDTH = 1170;
const int SCREEN_HEIGHT = 750;
const int BOTTOM_BAR_HEIGHT = 100;
// Added by Daniel
const int SCREEN_BPP = 32;

// constants for map grid of scenes
const int MAP_COLUMNS = 6;
const int MAP_ROWS = 8;

//Player dimension constants
const int PLAYER_WIDTH = 60;
const int PLAYER_HEIGHT = 60;
const double PLAYER_SPEED = 0.35;

//Enemy dimension constants
const int ENEMY_WIDTH = 60;
const int ENEMY_HEIGHT = 60;
const double ENEMY_SPEED = 0.15;

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


#endif