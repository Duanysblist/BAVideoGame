#include "bionic_apocalypse_battlelogic.h"

// resets all battle information and makes sure player is able to battle
void Battle::startNewBattle(Player &player, Enemy &enemy) {
	myEnemy = enemy;
	active = true;
	armored = false;
	enemyDOT = false;
	
	// keep track of bomb countdown
	bombSet = 0;
	// keep track of how many bombs are set
	numBombs = 0;

	enemyDebuff = false;
	checkAvailableMoves(player);
}

bool Battle::setAttackingTrue(Player &player, int move) {
	// if both are still alive
	if (player.getPlayerHealth() > 0 && myEnemy.getHealth() > 0) {
		// decrease player resources and impact player health 
		int playerMove = player.useMove(move);
		// if player does not have the resources for the chosen move
		if (playerMove == -1) {
			return false;
		}
		else { // player has the resources for the chosen move
			switch (playerMove)
			{
				case 0: {
					curPlayerMove = "Crowbar";
					playerDamage = 10;
					myEnemy.changeHealth(-playerDamage);
				}break;
				case 1: {
					curPlayerMove = "Bandages";
					playerDamage = 0;
				}break;
				case 2: {
					curPlayerMove = "Throwing Knives";
					// each knife deals 8 damage (24 damage total from all three), but randomly make some miss
					int chance = (rand() % 50);
					if (chance >= 20) {
						playerDamage = 24;
						myEnemy.changeHealth(-playerDamage);
					}
					else if (chance >= 15) {
						playerDamage = 16;
						myEnemy.changeHealth(-playerDamage);
					}
					else if (chance >= 10) {
						playerDamage = 8;
						myEnemy.changeHealth(-playerDamage);
					}
				}break;
				case 3: {
					curPlayerMove = "Block";
					playerDamage = 0;
					// set armored to true so that enemy's attack is blocked
					armored = true;
				}break;
				case 4: {
					curPlayerMove = "Molotov";
					playerDamage = 0;
					// set enemyDOT to true so that enemy gets recurring damage
					enemyDOT = true;
				}break;
				case 5: {
					curPlayerMove = "Electric Crowbar Strike";
					playerDamage = 25;
					myEnemy.changeHealth(-playerDamage);
				}break;
				case 6: {
					playerDamage = 0;
					curPlayerMove = "Time Bomb";
					if (bombSet == 0) {
						// set countdown for when bomb explodes
						bombSet = 3;
						numBombs = 1;
					}
					// if a bomb is already set, add more power to it (i.e. add another bomb)
					else {
						numBombs += 1;
					}
				}break;
				case 7: {
					curPlayerMove = "Electric Net";
					playerDamage = 5;
					myEnemy.changeHealth(-playerDamage);
					// set enemyDebuff to true so enemy might lose its turn
					enemyDebuff = true;
				}break;
				case 8: {
					playerDamage = 0;
					curPlayerMove = "Tourniquet";
				}break;
				case 9: {
					curPlayerMove = "Tactical Nuke";
					playerDamage = 50;
					myEnemy.changeHealth(-playerDamage);
				}break;
				case 10: {
					curPlayerMove = "Large Nuke";
					// kill the enemy
					playerDamage = myEnemy.getHealth();
					myEnemy.setHealth(0);
				}break;
				case 11: {
					curPlayerMove = "Nuclear Projectile";
					playerDamage = 20;
					myEnemy.changeHealth(-playerDamage);
					// set enemyDOT to true so that enemy gets recurring damage
					enemyDOT = true;
				}break;
			}
			if (enemyDOT) {
				// do recurring damage
				myEnemy.changeHealth(-5);
				playerDamage = playerDamage + 5;
			}
			// choose a random enemy attack
			enemyDamage = myEnemy.randomAttack();

			// check if a time bomb is going off
			int bombValue = bombHandler();
			if (bombValue != 0) { // bomb went off
				myEnemy.changeHealth(bombValue);
				playerDamage = playerDamage + bombValue;
				player.changePlayerHealth(-5);
			}
			if (armored) { // player has armor on
				// reduce enemy damage by half
				enemyDamage = enemyDamage / 2;
				// get rid of armor
				armored = false;
			}
			if (enemyDebuff) { // chance of enemy losing its turn
				int chance = (rand() % 5);
				if (chance == 1){
					enemyDamage = 0;
				}
				enemyDebuff = false;
			}
			// check if player won
			if (myEnemy.getHealth() <= 0) {
				if (player.getPlayerHealth() > 0) {
					// set number of resources player gets as reward 
					int itemDrop = (rand() % 2) + 2;
					for(int i = 0; i < itemDrop; i++){
						// randomly choose which resource the player gets (scrap metal, rags, or oil)
						int resourceDrop = (rand() % 3);
						player.setResource(resourceDrop, 1);
					}
					win = true;
				}
				// end battle
				active = false;
			}
			// reduce player health
			player.changePlayerHealth(enemyDamage);
			if (player.getPlayerHealth() <= 0) { // player died
				win = false;
				active = false;
			}	
		}
	}
	return true;
}

// check if battle is active
bool Battle::getStatus() const{
	return active;
}

// handle time bombs
int Battle::bombHandler() {
	// if no bombs are set, return 0 damage
	if (bombSet == 0) {
		return 0;
	}
	// if bomb countdown is done (at 1), return 20 damage * the number of bombs set
	else if (bombSet == 1) {
		bombSet = 0;
		int temp = numBombs;
		numBombs = 0;
		return temp * -20;
	}
	// otherwise, decrease the countdown
	else {
		bombSet -= 1;
		return 0;
	}
}

// check if the battle was won
bool Battle::getWin() const {
	return win;
}

// return the enemy HP -- necessary bc enemy object here is different from the enemy object in main
int Battle::getEnemyHP() const {
	return myEnemy.getHealth();
}

// return string of move name
std::string Battle::getCurMove() const{
	return curPlayerMove;
}

// return how much damage the enemy did
int Battle::getEnemyDamage() const{
	return enemyDamage;
}

// return how much damage the player did
int Battle::getPlayerDamage() const{
	return playerDamage;
}

// if player has no available moves, lose and end the battle
void Battle::checkAvailableMoves(Player &player) {
	if (player.hasAvailableMoves() == false){
		win = false;
		active = false;
	}
}