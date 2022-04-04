#ifndef BIONIC_APOCALYPSE_PLAYER_H
#define BIONIC_APOCALYPSE_PLAYER_H

#include "bionic_apocalypse_constants.h"

class Player {
    public:
        int getResource(int resourceType) const;
        void setResource(int resourceType, int amountToAdd);
        int getKeyResource(int resourceType) const;
        void setKeyResource(int resourceType);

        int getPlayerHealth() const;
        void setPlayerHealth(int newHealth);
        void changePlayerHealth(int healthAddition);

        int getPlayerScreenPositionX() const;
        int getPlayerScreenPositionY() const;
        void changePlayerScreenPosition(int changeX, int changeY);
        void setPlayerScreenPosition(int newX, int newY);
        void limitPlayerScreenPosition();
        int checkIfPlayerIsAtScreenBoundary() const;

        void playerMoveUp();
        void playerMoveDown();
        void playerMoveLeft();
        void playerMoveRight();

        void setRelationalPositionY(int newRelationalPositionY);
        void setRelationalPositionX(int newRelationalPositionY);
        void changeRelationalPositionY(int relPosAddition);
        void changeRelationalPositionX(int relPosAddition);
};

#endif