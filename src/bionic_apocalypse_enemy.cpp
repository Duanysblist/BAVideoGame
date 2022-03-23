#include "bionic_apocalypse_enemy.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>


int enemyHealth = 100;
int enemyAttacks [3] = { -4,-8,-12 };

int Enemy::getHealth() {
	return enemyHealth;
}

void Enemy::setHealth(int newHealth) {
	enemyHealth = newHealth;
}

//Adds or Subtracts from the health of the enemy
void Enemy::changeHealth(int healthChange) {
	enemyHealth += healthChange;
}

//Chooses a random attack from the enemy's arsenal
int Enemy::randomAttack() {
	int numOfAttacks = sizeof(enemyAttacks);
	int result = (rand() % numOfAttacks);
	return enemyAttacks[result];
}
