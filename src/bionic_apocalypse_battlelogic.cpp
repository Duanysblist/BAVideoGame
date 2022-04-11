#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_battlelogic.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

Enemy* mainEnemy;
bool active = false;

void startNewBattle(Enemy* enemy) {
	// std::cout << "battle and bad guy initiated" << std::endl; 
	mainEnemy = enemy;
	active = true;
}

void setAttackingTrue(Player* player) {
	if (player->getPlayerHealth() > 0 && mainEnemy->getHealth() > 0) {
		mainEnemy->changeHealth(-9);
		player->changePlayerHealth(mainEnemy->randomAttack());
		// std::cout << "Player HP: " << player.getPlayerHealth() << ", Enemy HP: " << mainEnemy.getHealth() << std::endl;
		// std::cout << "Attacking" << "\n";
	}
	else {
		active = false;
	}
}

bool getStatus() {
	return active;
}