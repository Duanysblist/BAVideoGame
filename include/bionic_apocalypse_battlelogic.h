#ifndef BIONIC_APOCALYPSE_BATTLELOGIC_H
#define BIONIC_APOCALYPSE_BATTLELOGIC_H

#include "bionic_apocalypse_player.h"

void startNewBattle(Enemy &enemy);

void mainBattleLoop();

void setAttackingTrue(Player &player);

bool getStatus();

#endif