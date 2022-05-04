#include "bionic_apocalypse_player.h"
#include <random>
#include <time.h>

int Player::getResource(const int resourceType) const {
	return inventory[resourceType];
}

void Player::setResource(const int resourceType, const int amountToAdd) {
	inventory[resourceType] += amountToAdd;
}

int Player::getKeyResource(const int resourceType) const {
	return key_inventory[resourceType];
}

void Player::setKeyResource(const int resourceType) {
	key_inventory[resourceType] = 1;
}

void Player::resetResources() {
	inventory[0] = 0;
	inventory[1] = 0;
	inventory[2] = 0;
	inventory[3] = 0;
	inventory[4] = 0;
	inventory[5] = 0;
	key_inventory[0] = 0;
	key_inventory[1] = 0;
	key_inventory[2] = 0;
	crowbar = false;
}


bool Player::getCrowbar() const {
	return crowbar;
}

void Player::setCrowbar(const bool crowbarPossessed) {
	crowbar = crowbarPossessed;
}

int Player::useMove(const int move){
	std::array<bool, 12> moves = getPossibleBattleMoves();
	if (moves[move]) {
		switch (move) {
			case 1: {
				setResource(1, -1);
				int heal = (rand() % 6 + 10);
				changePlayerHealth(heal);
			}break;
			case 2: {
				setResource(0, -1);
			}break;
			case 3: {
				setResource(0, -1);
			}break;
			case 4: {
				setResource(1, -1);
				setResource(2, -1);
			}break;
			case 5: {
				setResource(3, -1);
				int chance = (rand() % 20);
				if (chance == 1) {
					changePlayerHealth(-10);
				}
			}break;
			case 6: {
				setResource(0, -1);
				setResource(3, -1);
				setResource(4, -1);
			}break;
			case 7: {
				setResource(1, -1);
				setResource(3, -1);
				setResource(4, -1);
			}break;
			case 8: {
				setResource(1, -1);
				setResource(4, -1);
				int heal = (rand() % 6 + 20);
				changePlayerHealth(heal);
			}break;
			case 9: {
				setResource(5, -1);
				setResource(3, -1);
				setResource(4, -1);
				changePlayerHealth(-25);
			}break;
			case 10: {
				setResource(5, -3);
				setResource(3, -1);
				setResource(4, -1);
				changePlayerHealth(-50);
			}break;
			case 11: {
				setResource(2, -1);
				setResource(1, -1);
				setResource(5, -1);
				changePlayerHealth(-10);
			}break;
		}
		return move;
	}
	return -1;
}

bool Player::hasAvailableMoves() const{
	std::array<bool, 12> moves = getPossibleBattleMoves();
	for (int i = 0; i < 12; i++) {
		if (moves[i]) {
			return true;
		}
	}
	return false;
}

std::array<bool, 12> Player::getPossibleBattleMoves() const {
	/**
		0 (crowbar) crowbar strike - does a varying amount of damage to the enemy 
		1 (Rags) Bandages - Heal Player 
		2 (Scrap Metal) Throwing Knives - Player throws 3 knives; deals large damage but each has a 20% chance of missing
		3 (scrap metal) - defends player against half of the damage from the enemy's next attack, small chance of enemy's attack rebounding onto the enemy
		4 (Oil, Rags) Molotov - Does no damage to enemy but inflicts fire effect, which does recurring damage
		5 (power source, crowbar) electric crowbar strike - deals damage to enemy, small chance of player getting electrocuted and damaged as well
		6 (Power Source, Wire, Scrap Metal) Time Bomb - Takes 2 turns to activate but deals massive damage to enemy and some damage to player. consecutive bombs will blow on the earliest fuse timer.
		7 (Wire, Power Source, Rags) Electric net - Deals small damage to enemy, chance to shock them and have them miss their next turn
		8 (wire, rags) some sort of whip or trips enemy or something - deals minor damage to enemy and heals player
		9 (nuclear waste, wires, power source) small nuclear bomb - deals damage to enemy but also to player
		10 (3x nuclear waste, wires, power source) large nuclear bomb - kills enemy but deals large amount of damage to player 
		11 (oil, nuclear waste, rags) Nuclear projectile - deals small amount of damage to enemy, chance of recurring damage to enemy
	**/
	std::array<bool, 12> moves = {false,false,false,false,false,false,false,false,false,false,false,false};

	// check if each battle move is possible
	// regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

	if (crowbar) {
		moves[0] = true;
	}
	if (inventory[1] >= 1) {
		moves[1] = true;
	}
	if (inventory[0] >= 1) {
		moves[2] = true;
	}
	if (inventory[0] >= 1) {
		moves[3] = true;
	}
	if (inventory[1] >= 1 && inventory[2] >= 1) {
		moves[4] = true;
	}
	if (inventory[3] >= 1 && crowbar) {
		moves[5] = true;
	}
	if (inventory[3] >= 1 && inventory[4] >= 1 && inventory[0] >= 1) {
		moves[6] = true;
	}
	if (inventory[4] >= 1 && inventory[3] >= 1 && inventory[1] >= 1) {
		moves[7] = true;
	}
	if (inventory[4] >= 1 && inventory[1] >= 1) {
		moves[8] = true;
	}
	if (inventory[5] >= 1 && inventory[4] >= 1 && inventory[3] >= 1) {
		moves[9] = true;
	}
	if (inventory[5] >= 3 && inventory[4] >= 1 && inventory[3] >= 1) {
		moves[10] = true;
	}
	if (inventory[2] >= 1 && inventory[5] >= 1 && inventory[1] >= 1) {
		moves[11] = true;
	}

	return moves;
}

int Player::getPlayerHealth() const {
	return playerHealth;
}

void Player::setPlayerHealth(const int newHealth) {
	playerHealth = newHealth;
	if (playerHealth < 0) playerHealth = 0;
	if (playerHealth > MAX_HEALTH) playerHealth = MAX_HEALTH;
}

void Player::changePlayerHealth(const int healthAddition) {
	playerHealth += healthAddition;
	if (playerHealth < 0) playerHealth = 0;
	if (playerHealth > MAX_HEALTH) playerHealth = MAX_HEALTH;
}

void Player::setWalkingAnim(bool walk) {
	walkingAnim = walk;
}

bool Player::getWalkingAnim() const {
	return walkingAnim;
}

int Player::getPlayerScreenPositionX() const {
	return positionX;
}

int Player::getPlayerScreenPositionY() const {
	return positionY;
}

void Player::limitPlayerScreenPosition() {
	if (positionX < 0) {
		positionX = 0;
	}
	else if (positionX > (SCREEN_WIDTH - PLAYER_WIDTH)) {
		positionX = SCREEN_WIDTH - PLAYER_WIDTH;
	}
	else if (positionY < 0) {
		positionY = 0;
	}
	else if (positionY > (SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT)) {
		positionY = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT;
	}
}

// check if the player is at the edges of the screen
// If they are at the edge, check if there is a screen in that direction
// If there is, render that screen, if not do nothing
int Player::checkIfPlayerIsAtScreenBoundary() const {
	// if their x position is at 0
	if (positionX <= 0) {
		// Check if there is screen to the left
			// Get current player map position
				// if vector.at(1) is 0, they cannot move left
				if(playerMapPosition.at(1) == 0) {
					return 0;
				}
					//break;
				// otherwise, return 4 
		return 4;
	}
	// if their x position is at the right side of the screen
	if (positionX >= (SCREEN_WIDTH - PLAYER_WIDTH)){
		// Check if there is a right screen
			// Get current player map position
				// If the player is all the way to the right of the screen ([0][3], [1][3], [2][3], [3][3])
				if(playerMapPosition.at(1) == MAP_COLUMNS - 1) {
					// Can't move right
					return 0;
				}
		return 2;
	}
	// if their y position is at 0
	if (positionY <= 0) {
		// Check if there is a screen above
			// Get current player map position
				// If the player is in the top level of the map matrix ([0][0], [0][1], [0][2], [0][3])
				if(playerMapPosition.at(0) == 0){
					// Can't move up
					return 0;
				}
		return 1;
	}
	// if their y position is on the bottom of the screen
	if (positionY >= (SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT)){
		// Check if there is a screen below
			// Get current player map position
				// If the player is at the bottom level of the matrix ([3][0] [3][1] [3][2] [3][3])
				if(playerMapPosition.at(0) == MAP_ROWS - 1){
					// Can't move down
					return 0;
				}
		return 3;
	}

	// Return values correspond to Direction constants in constants file
	return 0;
	
}

void Player::changePlayerScreenPosition(const int changeX, const int changeY) {
	positionX += changeX;
	positionY += changeY;
	limitPlayerScreenPosition();

}

/*
The map should look like this:

[[1 0 0 0]
[0 0 0 0]
[0 0 0 0]
[0 0 0 0]]

0 [0][0] [0][1] [0][2] [0][3]
1 [1][0] [1][1] [1][2] [1][3]
2 [2][0] [2][1] [2][2] [2][3]
3 [3][0] [3][1] [3][2] [3][3]

We can have the player start in the top left hand corner scene 
map[0][0]

A right movement from here would go to map[0][1]

A downward movement would go to map[1][0]

Need to constantly check constriants to make sure player is at map >= 0 and <= 3

If the user is at these points, need to determine possible directions they can go
	If user is at map[min][x], the user cannot go up
	If user is at map[x][min], the user cannot go left
	If user is at map[max][x], the useer cannot go down
	If user is at map[x][max], the user cannot go right
*/

std::vector<int> Player::getPlayerMapPosition() const {
	return playerMapPosition;
}

void Player::setPlayerMapPosition(const std::vector<int> pos) {
	playerMapPosition = pos;
}

void Player::setPlayerScreenPosition(const int newX, const int newY) {
	positionX = newX;
	positionY = newY;
	limitPlayerScreenPosition();
}

void Player::playerMoveUp(const int dt) {
	int change = -PLAYER_SPEED * dt; 
	upDir = true;
	changePlayerScreenPosition(0, change);
}

void Player::playerMoveDown(const int dt) {
	int change = PLAYER_SPEED * dt; 
	upDir = false;
	changePlayerScreenPosition(0, change);
}

void Player::playerMoveLeft(const int dt) {
	int change = -PLAYER_SPEED * dt; 
	leftDir = true;
	changePlayerScreenPosition(change, 0);
}

void Player::playerMoveRight(const int dt) {
	int change = PLAYER_SPEED * dt; 
	leftDir = false;
	changePlayerScreenPosition(change, 0);
}

std::array<bool, 2> Player::getDirections() const {
	std::array<bool, 2> directions = {upDir, leftDir};
	return directions;
}
