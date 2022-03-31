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
bool active = false;

void startNewBattle(Enemy enemy) {
	std::cout << "battle and bad guy initiated" << std::endl; 
	mainEnemy = enemy;
	active = true;
}

void setAttackingTrue() {
	if (getPlayerHealth() > 0 && mainEnemy.getHealth() > 0) {
		mainEnemy.changeHealth(-9);
		changePlayerHealth(mainEnemy.randomAttack());
		std::cout << "Player HP: " << getPlayerHealth() << ", Enemy HP: " << mainEnemy.getHealth() << std::endl;
		std::cout << "Attacking" << "\n";
	}
	else {
		active = false;
	}
}

bool getStatus() {
	return active;
}