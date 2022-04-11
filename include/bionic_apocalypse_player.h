#ifndef BIONIC_APOCALYPSE_PLAYER_H
#define BIONIC_APOCALYPSE_PLAYER_H

#include "bionic_apocalypse_constants.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

class Player {
    private:
        int positionX = 0;
        int positionY = 0;
        int screenLocation;
        const int playerMovementSpeed = 10;

    public:

        int getResource(const int resourceType) const;
        void setResource(const int resourceType, const int amountToAdd);
        int getKeyResource(const int resourceType) const;
        void setKeyResource(const int resourceType);

        int getPlayerHealth() const;
        void setPlayerHealth(int newHealth);
        void changePlayerHealth(int healthAddition);

        int getPlayerScreenPositionX() const;
        int getPlayerScreenPositionY() const;
        void changePlayerScreenPosition(const int changeX, const int changeY);
        void setPlayerScreenPosition(const int newX, const int newY);
        void limitPlayerScreenPosition();
        int checkIfPlayerIsAtScreenBoundary() const;

        void playerMoveUp();
        void playerMoveDown();
        void playerMoveLeft();
        void playerMoveRight();

        void setRelationalPositionY(const int newRelationalPositionY);
        void setRelationalPositionX(const int newRelationalPositionY);
        void changeRelationalPositionY(const int relPosAddition);
        void changeRelationalPositionX(const int relPosAddition);

        std::vector<int> getPlayerMapPosition() const;
        void setPlayerMapPosition(std::vector<int> position);
};

#endif