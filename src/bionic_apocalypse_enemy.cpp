#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_constants.h"

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
int startLocation [2] = {500,500};
int endLocation [2] = {900,250};
bool goingToStart = false;

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
	std::cout << "Getting called X" << newX << "\n";
}

void Enemy::setPosY(int newY) {
	enemyPosY = newY;
	std::cout << "Getting called Y" << newY << "\n";
}

int Enemy::getX() {
	return enemyPosX;
}

int Enemy::getY() {
	return enemyPosY;
}

void Enemy::setStartLocation(int X, int Y) {
	startLocation[0] = X;
	startLocation[1] = Y;
}

void Enemy::setEndLocation(int X, int Y) {
	endLocation[0] = X;
	endLocation[1] = Y;
}

bool Enemy::playerCollisionCheck(Player player) {
	int playerX = player.getPlayerScreenPositionX();
	int playerY = player.getPlayerScreenPositionY();
	if ((playerX <= enemyPosX && playerX+PLAYER_WIDTH >= enemyPosX)||(playerX <= enemyPosX+ENEMY_WIDTH && playerX+PLAYER_WIDTH >= enemyPosX+ENEMY_WIDTH)&&
		(playerY <= enemyPosY && playerY+PLAYER_HEIGHT >= enemyPosY)||(playerY <= enemyPosY+ENEMY_HEIGHT && playerY+PLAYER_HEIGHT >= enemyPosY+ENEMY_HEIGHT)) {
			return true;
	}
	return false;
}

void Enemy::update(Renderer* renderer) {
	//Update Location
	std::cout << "Update";
	int distanceX;
	int distanceY;
	if (goingToStart) {
		distanceX = startLocation[0] - enemyPosX;
		distanceY = startLocation[1] - enemyPosY;
	}
	else {
		distanceX = endLocation[0] - enemyPosX;
		distanceY = endLocation[1] - enemyPosY;
	}

	std::cout << ", X Distance: " << distanceX << ", Y Distance: " << distanceY;
	
	if (distanceX > 0) {
		setPosX(enemyPosX+ENEMY_SPEED);
	}
	else if (distanceX < 0) {
		setPosX(enemyPosX-ENEMY_SPEED);
	} 
	if (distanceY > 0) {
		setPosY(enemyPosY+ENEMY_SPEED);
	}
	else if (distanceY < 0) {
		setPosY(enemyPosY-ENEMY_SPEED);
	}
	if (distanceY == 0 && distanceX == 0) {
		goingToStart = !goingToStart;
	}

	//Render Enemy
	renderer->drawEnemy(enemyPosX, enemyPosY);

	//Check Player Collision
	//playerCollisionCheck();
}

// void Enemy::draw(Renderer renderer) {
// 	if (alive) {
// 		renderer.drawEnemy(this);
// 		SDL_Delay(17);
// 	}
// }
