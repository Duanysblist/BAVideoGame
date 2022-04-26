#ifndef BIONIC_APOCALYPSE_BATTLELOGIC_H
#define BIONIC_APOCALYPSE_BATTLELOGIC_H

#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

class Battle {
    private:
        Enemy myEnemy;
        bool active = false;
    public:
        void startNewBattle(Enemy &enemy);
        void setAttackingTrue(Player &player, int move);
        bool getStatus();
};

#endif