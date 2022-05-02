#ifndef BIONIC_APOCALYPSE_CONSTANTS_H
#define BIONIC_APOCALYPSE_CONSTANTS_H

// Maximum player health
const int MAX_HEALTH = 100;

//Screen dimension constants -- DO NOT CHANGE UNLESS YOU'RE SURE THAT THE SCENE TILES WILL STAY AS SQUARES
const int SCREEN_WIDTH = 1170;
const int SCREEN_HEIGHT = 750;
const int BOTTOM_BAR_HEIGHT = 100;

// help screen dimensions
const int HELP_SCREEN_WIDTH = 960;
const int HELP_SCREEN_HEIGHT = 540;

// constants for map grid of scenes (i.e. how many scenes are in the map)
const int MAP_COLUMNS = 6;
const int MAP_ROWS = 8;

//Player constants
const int PLAYER_WIDTH = 40;
const int PLAYER_HEIGHT = 60;
const double PLAYER_SPEED = 0.35;

//Enemy constants
const int ENEMY_WIDTH = 35;
const int ENEMY_HEIGHT = 60;
const double ENEMY_SPEED = 0.15;

// Screen Directions
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;

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

const int LAB_LFW = 31; // left facing wall
const int LAB_RFW = 32; // right facing wall
const int LAB_UFW = 33; // up facing wall
const int LAB_DFW = 34; // down facing wall
const int LAB_PW = 35; // inner lab with no lights
const int LAB_ICTR = 36; // inner corner top right
const int LAB_ICTL = 37; // inner corner top left
const int LAB_ICBL = 38; // inner corner bottom left
const int LAB_ICBR = 39; // inner corner bottom right
const int LAB_OCTR = 40; // outer corner top right
const int LAB_OCTL = 41; // outer corner top left
const int LAB_OCBL = 42; // outer corner bottom left
const int LAB_OCBR = 43; // outer corner bottom right
const int LAB_LIGHTS = 44; // inner lab with lights

// Layouts for scenes in map

// [0, 0]
static int layout_0_0 [10][18]= 
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

// [0, 1]
static int layout_0_1 [10][18]= 
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

// [0, 2]
static int layout_0_2 [10][18]= 
  { {PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, OCBL},
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW}
};

// [0, 3]
static int layout_0_3 [10][18]= 
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

// [0, 4]
static int layout_0_4 [10][18]= 
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

// [0, 5]
static int layout_0_5 [10][18]= 
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


// [1, 0]
static int layout_1_0 [10][18]= 
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

// [1, 1] - displays [0, 7] in-game
static int layout_1_1 [10][18]= 
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

// [1, 2] - displays [0, 8] in-game
static int layout_1_2 [10][18]= 
  { {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {UFW, OCTR, 0, 0, 0, 0, 0, 0, OCTL, OCTR, 0, 0, 0, 0, 0, OCTL, UFW, UFW},
    {ICBR, OCBR, ROCK, ROCK, ROCK, ROCK, ROCK, ROCK, OCBL, OCBR, ROCK, ROCK, ROCK, ROCK, ROCK, LFW, PW, PW},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {ICTR, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL}, 
    {PW, PW, PW, PW, ICTR, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, ICTL}
};

// [1, 3]
static int layout_1_3 [10][18]= 
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

// [1, 4]
static int layout_1_4 [10][18]= 
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

// [1, 5]
static int layout_1_5 [10][18]= 
  { {DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, ICBL}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, ROCK, 0, 0, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, ROCK, 0, 0, 0, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, ROCK, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, ROCK, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, ICTR, OCTR, 0, 0, 0, 0, 0, LFW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, OCTL, ICTL}, 
};

// [2, 0]
static int layout_2_0 [10][18]= 
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

// [2, 1]
static int layout_2_1 [10][18]= 
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

// [2, 2]
static int layout_2_2 [10][18]= 
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

// [2, 3]
static int layout_2_3 [10][18]= 
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

// [2, 4]
static int layout_2_4 [10][18]= 
  { {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
    {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
    {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW}, 
    {DFW, DFW, OCBR, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW, PW, PW}, 
    {0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {0, 0, 0, 0, 0, LFW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
    {UFW, UFW, OCTR, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, LFW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL}, 
    {PW, PW, RFW, 0, 0, LFW, PW, ICTR, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, ICTL}, 
};

// [2, 5]
static int layout_2_5 [10][18]= 
  { {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW}, 
    {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, LFW, PW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW}, 
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL, PW}, 
    {PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
};

// [3, 0]
static int layout_3_0 [10][18]= 
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

// [3, 1]
static int layout_3_1 [10][18]= 
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

// [3, 2]
static int layout_3_2 [10][18]= 
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

// [3, 3]
static int layout_3_3 [10][18]= 
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

// [3, 4]
static int layout_3_4 [10][18]= 
  { {PW, PW, RFW, 0, 0, LFW, PW, ICBR, DFW, DFW, OCBR, 0, 0, OCBL, DFW, DFW, DFW, ICBL}, 
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

// [3, 5]
static int layout_3_5 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {OCBR, 0, 0, ROCK, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, ROCK, 0, 0, LFW}, 
    {0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_WIRE, TSVW, 0, 0, LFW}, 
    {0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, LFW}, 
    {OCTR, ROCK, ROCK, ROCK, 0, 0, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, TSHW, ROCK, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
};

// [4, 0]
static int layout_4_0 [10][18]= 
  { {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW, PW, PW}, 
    {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, OCBL, DFW, DFW},
    {RFW, 0, 0, ROCK, ROCK, ROCK, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, 0, 0, 0, 0, 0, LFW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, ROCK, ROCK, 0, 0, 0, LFW, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW},
    {RFW, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL} 
};

// [4, 1]
static int layout_4_1 [10][18]= 
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

// [4, 2]
static int layout_4_2 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {RFW, 0, 0, 0, 0, 0, LAB_OCTL, LAB_UFW, LAB_UFW, LAB_UFW, LAB_UFW, LAB_OCTR, 0, 0, 0, 0, 0, LFW},
    {OCBR, 0, 0, 0, 0, LAB_OCTL, LAB_ICTL, LAB_LIGHTS, LAB_PW, LAB_LIGHTS, LAB_PW, LAB_ICTR, LAB_OCTR, 0, 0, 0, 0, OCBL},
    {0, 0, 0, 0, 0, ROCK, LAB_LIGHTS, LAB_PW, LAB_PW, LAB_PW, LAB_PW, LAB_LIGHTS, LAB_RFW, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, ROCK, LAB_PW, LAB_PW, LAB_LIGHTS, LAB_PW, LAB_LIGHTS, LAB_PW, LAB_RFW, 0, 0, 0, 0, 0},
    {OCTR, 0, 0, 0, 0, LAB_OCBL, LAB_ICBL, LAB_PW, LAB_PW, LAB_LIGHTS, LAB_PW, LAB_ICBR, LAB_OCBR, 0, 0, 0, 0, OCTL},
    {RFW, 0, 0, 0, 0, 0, LAB_OCBL, LAB_DFW, LAB_DFW, LAB_DFW, LAB_DFW, LAB_OCBR, 0, 0, 0, 0, 0, LFW},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {ICTR, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, ICTL} 
};


// [4, 3]
static int layout_4_3 [10][18]= 
  { {PW, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, ICBL}, 
    {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {DFW, DFW, DFW, ICBL, PW, PW, RFW, 0, 0, OCTL, UFW, UFW, UFW, UFW, OCTR, 0, 0, LFW}, 
    {0, 0, 0, OCBL, DFW, DFW, OCBR, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, LFW}, 
    {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, OCBR, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
};

// [4, 4]
static int layout_4_4 [10][18]= 
  { {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, OCBL, DFW, DFW, DFW, DFW}, 
    {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
    {PW, PW, RFW, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, RFW, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
    {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, ICTR, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}, 
};

// [4, 5]
static int layout_4_5 [10][18]= 
  { {DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
    {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW}, 
    {DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},  
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
};

// [5, 0]
static int layout_5_0 [10][18]= 
  { {PW, PW, PW, PW, PW, PW, RFW, 0, 0, OCBL, ICBL, PW, PW, PW, PW, PW, PW, PW}, 
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

// [5, 1]
static int layout_5_1 [10][18]= 
  { {PW, PW, PW, PW, PW, PW, PW, ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, 0, 0, 0, METAL, 0, LFW},
    {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {PW, PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},
    {PW, PW, PW, PW, PW, PW, PW, ICTR, UFW, OCTR, 0, 0, OCTL, UFW, UFW, UFW, UFW, ICTL} 
};

// [5, 2]
static int layout_5_2 [10][18]= 
  { {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, PW, PW, PW, PW, RFW, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, PW, ICBR, DFW, DFW, OCBR, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW}, 
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, ROCK, ROCK, OCBL, DFW, DFW, DFW, DFW, DFW, DFW}, 
    {PW, PW, PW, RFW, 0, 0, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {PW, PW, PW, ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW}
};

// [5, 3]
static int layout_5_3 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, ROCK, ROCK, 0, 0, OCTL, UFW, UFW, UFW, OCTR, 0, 0, 0, 0, ROCK, LFW}, 
    {RFW, 0, 0, ROCK, 0, 0, 0, LFW, PW, PW, PW, RFW, ROCK, ROCK, 0, 0, ROCK, LFW}, 
    {OCBR, 0, 0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, LFW}, 
    {0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, LFW}, 
    {OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}
};

// [5, 4]
static int layout_5_4 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
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

// [5, 5]
static int layout_5_5 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, ROCK, 0, KEY_NUCLEAR, 0, ROCK, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, ROCK, ROCK, ROCK, ROCK, ROCK, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},  
    {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, OCTR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, ICTL}, 
};

// [6, 0]
static int layout_6_0 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICDB, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, OCBL},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCTL},
    {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, TSHW, TSHW, TSHW, TSHW, TSHW, ICDL},
    {RFW, 0, 0, 0, TSVW, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, LFW},
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, CROWBAR, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, TSVW, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICDT, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL} 
};

// [6, 1]
static int layout_6_1 [10][18]= 
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

// [6, 2]
static int layout_6_2 [10][18]= 
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

// [6, 3]
static int layout_6_3 [10][18]= 
  { {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {RFW, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {RFW, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {RFW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {OCBR, 0, 0, 0, OCTL, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
    {0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {0, 0, 0, 0, LFW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}, 
    {UFW, UFW, UFW, UFW, ICTL, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW, PW}
};

// [6, 4]
static int layout_6_4 [10][18]= 
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

// [6, 5]
static int layout_6_5 [10][18]= 
  { {DFW, DFW, DFW, DFW, DFW, DFW, DFW, OCBR, 0, 0, 0, OCBL, DFW, DFW, DFW, DFW, DFW, ICBL}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, ROCK, ROCK, ROCK, OCTL, UFW, UFW, UFW, OCTR, 0, 0, 0, ROCK, ROCK, 0, 0, LFW}, 
    {0, 0, ROCK, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, 0, ROCK, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, LFW, PW, PW, PW, RFW, ROCK, ROCK, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, OCBL, DFW, DFW, DFW, OCBR, 0, 0, 0, 0, 0, ROCK, ROCK, LFW}, 
    {0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW},  
    {0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, OCTL, OCTR, 0, 0, 0, 0, LFW},  
};

// [7, 0]
static int layout_7_0 [10][18]= 
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

// [7, 1]
static int layout_7_1 [10][18]= 
  { {ICBR, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW, DFW}, 
    {RFW, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {OCBR, 0, 0, 0, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, OCTL, UFW, UFW},
    {0, 0, 0, 0, 0, ROCK, ROCK, 0, 0, 0, ROCK, 0, 0, 0, 0, LFW, PW, PW},
    {0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, ROCK, ROCK, LFW, PW, PW},
    {OCTR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, OCBL, DFW, DFW},
    {RFW, ROCK, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {RFW, ROCK, ROCK, ROCK, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {ICTR, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW} 
};

// [7, 2]
static int layout_7_2 [10][18]= 
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

// [7, 3]
static int layout_7_3 [10][18]= 
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

// [7, 4]
static int layout_7_4 [10][18]= 
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

// [7, 5]
static int layout_7_5 [10][18]= 
  { {0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, OCBL, OCBR, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, ROCK, ROCK, 0, 0, ROCK, ROCK, 0, 0, 0, 0, 0, 0, ROCK, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, ROCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, ROCK, 0, 0, 0, ROCK, 0, 0, 0, 0, ROCK, 0, 0, 0, 0, LFW}, 
    {0, 0, 0, ROCK, 0, 0, ROCK, ROCK, ROCK, 0, 0, ROCK, ROCK, 0, 0, ROCK, ROCK, LFW}, 
    {UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, UFW, ICTL}, 
};


#endif