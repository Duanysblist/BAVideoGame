#include "bionic_apocalypse_enemy.h"


int Enemy::getHealth() const {
	return enemyHealth;
}

void Enemy::setHealth(const int newHealth) {
	enemyHealth = newHealth;
}

//Adds or Subtracts from the health of the enemy
void Enemy::changeHealth(const int healthChange) {
	enemyHealth += healthChange;
}

//Chooses a random attack from the enemy's arsenal
int Enemy::randomAttack() const {
	int numOfAttacks = sizeof(enemyAttacks)/sizeof(enemyAttacks[0]);
	int result = (rand() % numOfAttacks);
	return enemyAttacks[result];
}

void Enemy::setPosX(const int newX) {
	enemyPosX = newX;
	// std::cout << "Getting called X" << newX << "\n";
}

void Enemy::setPosY(const int newY) {
	enemyPosY = newY;
	// std::cout << "Getting called Y" << newY << "\n";
}

int Enemy::getX() const {
	return enemyPosX;
}

int Enemy::getY() const {
	return enemyPosY;
}

void Enemy::setStartLocation(const int X, const int Y) {
	startLocation[0] = X;
	startLocation[1] = Y;
}

void Enemy::setEndLocation(const int X, const int Y) {
	endLocation[0] = X;
	endLocation[1] = Y;
}

bool Enemy::playerCollisionCheck(const Player player) const {
	int playerX = player.getPlayerScreenPositionX();
	int playerY = player.getPlayerScreenPositionY();
	if ((playerX <= enemyPosX && playerX+PLAYER_WIDTH >= enemyPosX)||(playerX <= enemyPosX+ENEMY_WIDTH && playerX+PLAYER_WIDTH >= enemyPosX+ENEMY_WIDTH)&&
		(playerY <= enemyPosY && playerY+PLAYER_HEIGHT >= enemyPosY)||(playerY <= enemyPosY+ENEMY_HEIGHT && playerY+PLAYER_HEIGHT >= enemyPosY+ENEMY_HEIGHT)) {
			return true;
	}
	return false;
}

void Enemy::update(const int dt) {
	//Update Location
	// std::cout << "Update";
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

	// std::cout << ", X Distance: " << distanceX << ", Y Distance: " << distanceY;
	
	if (distanceX > 0) {
		setPosX(enemyPosX+(ENEMY_SPEED*dt));
	}
	else if (distanceX < 0) {
		setPosX(enemyPosX-(ENEMY_SPEED*dt));
	} 
	if (distanceY > 0) {
		setPosY(enemyPosY+(ENEMY_SPEED*dt));
	}
	else if (distanceY < 0) {
		setPosY(enemyPosY-(ENEMY_SPEED*dt));
	}
	if (distanceY == 0 && distanceX == 0) {
		goingToStart = !goingToStart;
	}

	//Render Enemy
	//renderer->drawEnemy(enemyPosX, enemyPosY);

}

void Enemy::setType(const int type) {
	enemyType = type;
	switch (enemyType)
	{
		case -1: {
			enemyHealth = 100;
			int newAttacks[3] = {-4, -5, -6};
			memcpy(enemyAttacks, newAttacks, sizeof(enemyAttacks));
		}break;
		case 1: {
			enemyHealth = 30;
			int newAttacks[3] = {-15, -20, -25};
			memcpy(enemyAttacks, newAttacks, sizeof(enemyAttacks));
		}break;
		case 0: {
			enemyHealth = 50;
			int newAttacks[3] = {-5, -10, -15};
			memcpy(enemyAttacks, newAttacks, sizeof(enemyAttacks));
		}
	}
}

void Enemy::setAlive(const bool stat) {
	alive = stat;
}

bool Enemy::getAlive() const{
	return alive;
}
