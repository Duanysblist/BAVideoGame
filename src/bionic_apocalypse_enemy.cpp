#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_renderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

bool alive = true;
int enemyHealth = 100;
int enemyAttacks [3] = { -4,-8,-12 };
int enemyPosX;
int enemyPosY;

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

void Enemy::setPosX(int newX) {
	enemyPosX = newX;
}

void Enemy::setPosY(int newY) {
	enemyPosY = newY;
}

int Enemy::getX() {
	return enemyPosX;
}

int Enemy::getY() {
	return enemyPosY;
}

void Enemy::draw() {
	if (alive) {
		drawEnemy(this);
		SDL_Delay(17);
	}
}
