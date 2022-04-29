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

const int HELP_SCREEN_WIDTH = 960;
const int HELP_SCREEN_HEIGHT = 540;

// constants for map grid of scenes
const int MAP_COLUMNS = 6;
const int MAP_ROWS = 8;

//Player dimension constants
const int PLAYER_WIDTH = 40;
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

// obstacle keywords
const int LFW = 11; // left facing wall
const int RFW = 12; // right facing wall
const int UFW = 13; // up facing wall
const int DFW = 14; // down facing wall
const int TSVW = 15; // two sided vertical wall
const int TSHW = 16; // two sided horizontal wall
const int PW = 17; // plain wall
const int ICTR = 18; // inner corner top right
const int ICTL = 19; // inner corner top left
const int ICBL = 20; // inner corner bottom left
const int ICBR = 21; // inner corner bottom right
const int OCTR = 22; // outer corner top right
const int OCTL = 23; // outer corner top left
const int OCBL = 24; // outer corner bottom left
const int OCBR = 25; // outer corner bottom right
const int ICDB = 26; // inner corner double bottom
const int ICDT = 27; // inner corner double top
const int ICDL = 28; // inner corner double left
const int ICDR = 29; // inner corner double right

// 1 - space in scene has rock obstacle
const int ROCK = 1;
// 2 - space in scene has scrap metal
const int METAL = 2;
// 3 - space in scene has rags
const int RAGS = 3;
// 4 - space in scene has oil
const int OIL = 4;
// 5 - space in scene has power source
const int POWER = 5;
// 6 - space in scene has wire
const int WIRE = 6;
// 7 - space in scene has nuclear waste
const int NUCLEAR = 7;

// 8 - space in scene has key resource power source
const int KEY_POWER = 8;
// 9 - space in scene has key resource wire
const int KEY_WIRE = 9;
// 10 - space in scene has key resource nuclear waste
const int KEY_NUCLEAR = 10;

// 30 - scene has crowbar
const int CROWBAR = 30;


#endif