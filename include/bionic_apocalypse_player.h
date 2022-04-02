#ifndef BIONIC_APOCALYPSE_PLAYER_H
#define BIONIC_APOCALYPSE_PLAYER_H

#include "bionic_apocalypse_constants.h"

int getResource(int resourceType);

void setResource(int resourceType, int amountToAdd);


int getPlayerHealth();

void setPlayerHealth(int newHealth);

void changePlayerHealth(int healthAddition);


int getPlayerScreenPositionX();

int getPlayerScreenPositionY();

void changePlayerScreenPosition(int changeX, int changeY);

void setPlayerScreenPosition(int newX, int newY);

void playerMoveUp();

void playerMoveDown();

void playerMoveLeft();

void playerMoveRight();


void setRelationalPositionY(int newRelationalPositionY);

void setRelationalPositionX(int newRelationalPositionY);

void changeRelationalPositionX(int relPosAddition);

void changeRelationalPositionY(int relPosAddition);

#endif