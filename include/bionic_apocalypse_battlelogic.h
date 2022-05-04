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
        bool armored = false;
        bool enemyDOT = false;
        int bombSet = 0;
        int numBombs = 0;
        bool enemyDebuff = false;
        bool win;
        int enemyDamage;
        std::string curPlayerMove = "";
        int playerDamage = 0;
    public:
        void startNewBattle(Player &player, Enemy &enemy);
        void setAttackingTrue(Player &player, int move);
        bool getStatus() const;
        int bombHandler();
        bool getWin() const;
        int getEnemyHP() const;
        std::string getCurMove() const;
        int getEnemyDamage() const;
        int getPlayerDamage() const;
        void checkAvailableMoves(Player &player);
};

#endif