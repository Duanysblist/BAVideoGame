#include "bionic_apocalypse_enemy.h"
//#include "bionic_apocalypse_enemy.cpp"
#include "bionic_apocalypse_player.h"
//#include "bionic_apocalypse_player.cpp"
#include "bionic_apocalypse_battlelogic.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

Enemy mainEnemy;
bool attackHappening = false;

void startNewBattle(const Enemy enemy) {
	mainEnemy = enemy;
	mainBattleLoop();
}

void mainBattleLoop() {
	while (getPlayerHealth() > 0 || mainEnemy.getHealth() > 0) {
		if (attackHappening) {
			mainEnemy.changeHealth(-9);
			changePlayerHealth(mainEnemy.randomAttack());
			attackHappening = false;
		}
	}
}

void setAttackingTrue() {
	attackHappening = true;
	std::cout << "True";
}