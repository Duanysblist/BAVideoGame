#include "bionic_apocalypse_player.h"

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

std::array<bool, 12> Player::getPossibleBattleMoves() const {
	/**
		0 (Rags) Bandages - Heal Player
		1 (Oil, Rags) Molotov - Does no damage to enemy but inflicts fire effect, which does recurring damage
		2 (Scrap Metal) Throwing Knives - Player throws 3 knives; deals large damage but each has a chance of missing
		3 (3x Scrap Metal) Armor Plate - Player gains increased temporary health (loses it after battle ends and can stack)
		4 (Power Source, Wire, Scrap Metal) Time Bomb - Takes 2 turns to activate but deals massive damage to enemy and some damage to player when it does
		5 (wire, rags) some sort of whip or trips enemy or something - deals minor damage to enemy
		6 (nuclear waste, wires, power source) small nuclear bomb - deals damage to enemy but also to player
		7 (3x nuclear waste, wires, power source) large nuclear bomb - kills enemy but deals large amount of damage to player 
		8 (scrap metal) - defends player against half of the damage from the enemy's next attack, small chance of enemy's attack rebounding onto the enemy
		9 (Wire, Power Source, Rags) Electric net - Deals small damage to enemy, chance to shock them and have them miss their next turn
		10 (power source) electric crowbar strike - deals damage to enemy, small chance of player getting electrocuted and damaged as well
		11 (oil, nuclear waste, rags) Nuclear projectile - deals small amount of damage to enemy, chance of recurring damage to enemy
	**/
	std::array<bool, 12> moves = {false,false,false,false,false,false,false,false,false,false,false,false};

	// check if each battle move is possible
	// regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

	if (inventory[1] >= 1) {
		moves[0] = true;
	}
	if (inventory[1] >= 1 && inventory[2] >= 1) {
		moves[1] = true;
	}
	if (inventory[0] >= 1) {
		moves[2] = true;
	}
	if (inventory[0] >= 3) {
		moves[3] = true;
	}
	if (inventory[3] >= 1 && inventory[4] >= 1 && inventory[0] >= 1) {
		moves[4] = true;
	}
	if (inventory[4] >= 1 && inventory[1] >= 1) {
		moves[5] = true;
	}
	if (inventory[5] >= 1 && inventory[4] >= 1 && inventory[3] >= 1) {
		moves[6] = true;
	}
	if (inventory[5] >= 3 && inventory[4] >= 1 && inventory[3] >= 1) {
		moves[7] = true;
	}
	if (inventory[0] >= 1) {
		moves[8] = true;
	}
	if (inventory[4] >= 1 && inventory[3] >= 1 && inventory[1] >= 1) {
		moves[9] = true;
	}
	if (inventory[3] >= 1) {
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
}

void Player::changePlayerHealth(const int healthAddition) {
	playerHealth += healthAddition;
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
	changePlayerScreenPosition(0, change);
}

void Player::playerMoveDown(const int dt) {
	int change = PLAYER_SPEED * dt; 
	changePlayerScreenPosition(0, change);
}

void Player::playerMoveLeft(const int dt) {
	int change = -PLAYER_SPEED * dt; 
	changePlayerScreenPosition(change, 0);
}

void Player::playerMoveRight(const int dt) {
	int change = PLAYER_SPEED * dt; 
	changePlayerScreenPosition(change, 0);
}
