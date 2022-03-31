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
bool active = false;

void startNewBattle(const Enemy enemy) {
	mainEnemy = enemy;
	active = true;
	mainBattleLoop();
	active = false;
}

void mainBattleLoop() {
	while (getPlayerHealth() > 0 || mainEnemy.getHealth() > 0) {
		if (attackHappening) {
			mainEnemy.changeHealth(-9);
			changePlayerHealth(mainEnemy.randomAttack());
			attackHappening = false;
			std::cout << getPlayerHealth() << ", Enemy HP: " << mainEnemy.getHealth() << "\n";
		}
	}
}

void setAttackingTrue() {
	attackHappening = true;
	std::cout << "Attacking" << "\n";
}

bool getStatus() {
	return active;
}