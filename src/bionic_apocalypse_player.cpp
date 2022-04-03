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

int Player::getResource(int resourceType) {
	return inventory[resourceType];
}

void Player::setResource(int resourceType, int amountToAdd) {
	inventory[resourceType] += amountToAdd;
}

int Player::getKeyResource(int resourceType) {
	return key_inventory[resourceType];
}

void Player::setKeyResource(int resourceType) {
	key_inventory[resourceType] = 1;
}

int Player::getPlayerHealth() {
	return playerHealth;
}

void Player::setPlayerHealth(int newHealth) {
	playerHealth = newHealth;
}

void Player::changePlayerHealth(int healthAddition) {
	playerHealth += healthAddition;
}


int Player::getPlayerScreenPositionX() {
	return positionX;
}

int Player::getPlayerScreenPositionY() {
	return positionY;
}

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

void Player::changePlayerScreenPosition(int changeX, int changeY) {
	positionX += changeX;
	positionY += changeY;
	limitPlayerScreenPosition();
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