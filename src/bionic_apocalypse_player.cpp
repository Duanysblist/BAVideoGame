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

int getResource(int resourceType) {
	return inventory[resourceType];
}

void setResource(int resourceType, int amountToAdd) {
	inventory[resourceType] += amountToAdd;
}

int getKeyResource(int resourceType) {
	return key_inventory[resourceType];
}

void setKeyResource(int resourceType) {
	key_inventory[resourceType] = 1;
}

int getPlayerHealth() {
	return playerHealth;
}

void setPlayerHealth(int newHealth) {
	playerHealth = newHealth;
}

void changePlayerHealth(int healthAddition) {
	playerHealth += healthAddition;
}


int getPlayerScreenPositionX() {
	return positionX;
}

int getPlayerScreenPositionY() {
	return positionY;
}

void limitPlayerScreenPosition() {
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

void changePlayerScreenPosition(int changeX, int changeY) {
	positionX += changeX;
	positionY += changeY;
	limitPlayerScreenPosition();
}

void setPlayerScreenPosition(int newX, int newY) {
	positionX = newX;
	positionY = newY;
	limitPlayerScreenPosition();
}

void playerMoveUp() {
	changePlayerScreenPosition(0, -playerMovementSpeed);
}

void playerMoveDown() {
	changePlayerScreenPosition(0, playerMovementSpeed);
}

void playerMoveLeft() {
	changePlayerScreenPosition(-playerMovementSpeed, 0);
}

void playerMoveRight() {
	changePlayerScreenPosition(playerMovementSpeed, 0);
}


void setRelationalPositionY(int newRelationalPositionY) {

}

void setRelationalPositionX(int newRelationalPositionY) {

}

void changeRelationalPositionX(int relPosAddition) {

}

void changeRelationalPositionY(int relPosAddition) {

}