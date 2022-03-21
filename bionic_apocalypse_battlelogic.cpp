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
	while (playerHealth > 0 || mainEnemy.getHealth() > 0) {
		if (attackHappening) {
			mainEnemy.changeHealth(-9);
			changePlayerHealth(mainEnemy.randomAttack());
		}
	}
}

void setAttackingTrue() {
	attackHappening = true;
}