#include "bionic_apocalypse_battlelogic.h"

void Battle::startNewBattle(Enemy &enemy) {
	// std::cout << "battle and bad guy initiated" << std::endl; 
	myEnemy = enemy;
	active = true;
	armored = false;
	enemyDOT = false;
	bombSet = 0;
	numBombs = 0;
	enemyDebuff = false;
}

void Battle::setAttackingTrue(Player &player, int move) {
	if (player.getPlayerHealth() > 0 && myEnemy.getHealth() > 0) {
		int playerMove = player.useMove(move);
		if (playerMove == -1) {
			//display something about not having the right materials for using that ability
		}
		else {
			switch (playerMove)
			{
				case 0: {
					myEnemy.changeHealth(-10);
				}break;
				case 2: {
					int chance = (rand() % 50);
					if (chance >= 20) {
						myEnemy.changeHealth(-24);
					}
					else if (chance >= 15) {
						myEnemy.changeHealth(-16);
					}
					else if (chance >= 10) {
						myEnemy.changeHealth(-8);
					}
				}break;
				case 3: {
					armored = true;
				}break;
				case 4: {
					enemyDOT = true;
				}break;
				case 5: {
					myEnemy.changeHealth(-25);
				}break;
				case 6: {
					if (bombSet == 0) {
						bombSet = 3;
						numBombs = 1;
					}
					else {
						numBombs += 1;
					}
				}break;
				case 7: {
					myEnemy.changeHealth(-5);
					enemyDebuff = true;
				}break;
				case 9: {
					myEnemy.changeHealth(-50);
				}break;
				case 10: {
					myEnemy.setHealth(0);
				}break;
				case 11: {
					myEnemy.changeHealth(-20);
					enemyDOT = true;
				}break;
			}
			if (enemyDOT) {
				myEnemy.changeHealth(-5);
			}
			int bombValue = bombHandler();
			if (bombValue != 0) {
				myEnemy.changeHealth(bombValue);
				player.changePlayerHealth(-5);
			}
			int enemyDamage = myEnemy.randomAttack();
			if (armored) {
				if (enemyDamage % 2) {
					enemyDamage = (enemyDamage + 1) / 2;
				}
				else {
					enemyDamage = enemyDamage / 2;
				}
			}
			if (enemyDebuff) {
				int chance = (rand() % 5);
				if (chance == 1){
					enemyDamage = 0;
				}
			}
			player.changePlayerHealth(enemyDamage);
		}
		//std::cout << "Player HP: " << player.getPlayerHealth() << ", Enemy HP: " << mainEnemy.getHealth() << std::endl;
		// std::cout << "Attacking" << "\n";
	}
	else {
		if (player.getPlayerHealth() > 0) {
			int itemDrop = (rand() % 2) + 2;
			for(int i = 0; i < itemDrop; i++){
				int resourceDrop = (rand() % 4);
				player.setResource(resourceDrop, 1);
			}
			win = true;
		}
		else {
			win = false;
		}
		active = false;
		std::cout << "done with battle" << "\n";
	}
}

bool Battle::getStatus() const{
	return active;
}

int Battle::bombHandler() {
	if (bombSet == 0) {
		return 0;
	}
	else if (bombSet == 1) {
		bombSet = 0;
		int temp = numBombs;
		numBombs = 0;
		return temp * -20;
	}
	else {
		bombSet -= 1;
		return 0;
	}
}

bool Battle::getWin() const {
	return win;
}

int Battle::getEnemyHP() const {
	return myEnemy.getHealth();
}