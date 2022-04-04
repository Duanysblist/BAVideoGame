#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "bionic_apocalypse_constants.h"
#include "bionic_apocalypse_player.h"

int positionX = 0;
int positionY = 0;
int screenLocation;
int playerHealth = MAX_HEALTH - 20;
int playerMovementSpeed = 10;

// inventories
// regular inventory: { sheet metal, rags, oil, power source, wire, nuclear waste }
int inventory [6] = { 0,0,0,0,0,0 };
// key inventory: { large power source, long wire, large nuclear waste }
int key_inventory [3] = { 0,0,0 };

int Player::getResource(int resourceType) const {
	return inventory[resourceType];
}

void Player::setResource(int resourceType, int amountToAdd) {
	inventory[resourceType] += amountToAdd;
}

int Player::getKeyResource(int resourceType) const {
	return key_inventory[resourceType];
}

void Player::setKeyResource(int resourceType) {
	key_inventory[resourceType] = 1;
}

int Player::getPlayerHealth() const {
	return playerHealth;
}

void Player::setPlayerHealth(int newHealth) {
	playerHealth = newHealth;
}

void Player::changePlayerHealth(int healthAddition) {
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
	if (positionX > (SCREEN_WIDTH - PLAYER_WIDTH)) {
		positionX = SCREEN_WIDTH - PLAYER_WIDTH;
	}
	if (positionY < 0) {
		positionY = 0;
	}
	if (positionY > (SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT)) {
		positionY = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT;
	}
}

// Need a method that cna check if the player is at the edges of the screen
// If they are at the edge, need to check if there is a screen in that direction
// If there is, render that screen, if not do nothing
int Player::checkIfPlayerIsAtScreenBoundary() const {
	// if their x position is at 0
	if (positionX <= 0) {
		// Check if there is screen to the left
			// TODO: Find a way to check existence of another screen
		return 4;
	}
	// if their x position is at the right side of the screen
	if (positionX > (SCREEN_WIDTH - PLAYER_WIDTH)){
		// Check if there is a right screen
		return 2;
	}
	// if their y position is at 0
	if (positionY <= 0) {
		// Check if there is a screen above
		return 1;
	}
	// if their y position is on the bottom of the screen
	if (positionY > (SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT)){
		// Check if there is a screen below
		return 3;
	}

	// Return values correspond to Direction constants in constants file
	return 0;
	
}

void Player::changePlayerScreenPosition(int changeX, int changeY) {
	positionX += changeX;
	positionY += changeY;
	switch(checkIfPlayerIsAtScreenBoundary()) {
		case 0:
			// The player is not at the edge of the screen
			break;
		case 1:
			// Move to above screen
			// Don't change x value; y value turns from 0 to SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT
			// setPlayerScreenPosition(sameX, newY)
			break;
		case 2:
			// Move to right screen
			// Don't change y value; x value goes from SCREEN_WIDTH - PLAYER_WIDTH to 0
			// setPlayerScreenPosition(newX, sameY)
			break;
		case 3:
			// Move to below screen
			// Don't change x value; y value turns from SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT - PLAYER_HEIGHT to 0
			// setPlayerScreenPosition(sameX, newY)
			break;
		case 4:
			// Move to left screen
			// Don't change y value; x value goes fromo 0 to SCREEN_WIDTH - PLAYER_WIDTH
			// setPlayerScreenPosition(newX, sameY)
			break;
	}

}

void Player::setPlayerScreenPosition(int newX, int newY) {
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


void Player::setRelationalPositionY(int newRelationalPositionY) {

}

void Player::setRelationalPositionX(int newRelationalPositionY) {

}

void Player::changeRelationalPositionX(int relPosAddition) {

}

void Player::changeRelationalPositionY(int relPosAddition) {

}