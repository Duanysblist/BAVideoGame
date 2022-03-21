#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

class Enemy {
	int enemyHealth = 100;
	int enemyAttacks [3] = { -4,-8,-12 };

	int getHealth() {
		return enemyHealth;
	}

	void setHealth(int newHealth) {
		enemyHealth = newHealth;
	}

	//Adds or Subtracts from the health of the enemy
	void changeHealth(int healthChange) {
		enemyHealth += healthChange;
	}

	//Chooses a random attack from the enemy's arsenal
	int randomAttack() {
		numOfAttacks = enemyAttacks.length;
		int result = (rand() % numOfAttacks);
		return enemyAttacks[result];
	}
};

