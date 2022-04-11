#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "bionic_apocalypse_constants.h"
#include "bionic_apocalypse_player.h"

int playerHealth = MAX_HEALTH;

// For map position
std::vector<int> playerMapPosition(2, 0);

// inventories
// regular inventory: { sheet metal, rags, oil, power source, wire, nuclear waste }
int inventory [6] = { 0,0,0,0,0,0 };
// key inventory: { large power source, long wire, large nuclear waste }
int key_inventory [3] = { 0,0,0 };

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

// This needs to either be changed or gotten rid of for screen to screen movement
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
	else {
		positionX = positionX;
		positionY = positionY;
	}
}

// Need a method that can check if the player is at the edges of the screen
// If they are at the edge, need to check if there is a screen in that direction
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
				if(playerMapPosition.at(1) == 3) {
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
				if(playerMapPosition.at(0) == 3){
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

void Player::playerMoveUp() {
	changePlayerScreenPosition(0, -playerMovementSpeed);
}

void Player::playerMoveDown() {
	changePlayerScreenPosition(0, playerMovementSpeed);
}

void Player::playerMoveLeft() {
	changePlayerScreenPosition(-playerMovementSpeed, 0);
}

void Player::playerMoveRight() {
	changePlayerScreenPosition(playerMovementSpeed, 0);
}


void Player::setRelationalPositionY(const int newRelationalPositionY) {

}

void Player::setRelationalPositionX(const int newRelationalPositionY) {

}

void Player::changeRelationalPositionX(const int relPosAddition) {

}

void Player::changeRelationalPositionY(const int relPosAddition) {

}