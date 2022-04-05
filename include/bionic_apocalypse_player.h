#ifndef BIONIC_APOCALYPSE_PLAYER_H
#define BIONIC_APOCALYPSE_PLAYER_H

#include "bionic_apocalypse_constants.h"
#include <vector>

class Player {
    public:
        int getResource(int resourceType);
        void setResource(int resourceType, int amountToAdd);
        int getKeyResource(int resourceType);
        void setKeyResource(int resourceType);

        int getPlayerHealth();
        void setPlayerHealth(int newHealth);
        void changePlayerHealth(int healthAddition);

        int getPlayerScreenPositionX();
        int getPlayerScreenPositionY();
        void changePlayerScreenPosition(int changeX, int changeY);
        void setPlayerScreenPosition(int newX, int newY);
        void limitPlayerScreenPosition();
        int checkIfPlayerIsAtScreenBoundary();

        void playerMoveUp();
        void playerMoveDown();
        void playerMoveLeft();
        void playerMoveRight();

        void setRelationalPositionY(int newRelationalPositionY);
        void setRelationalPositionX(int newRelationalPositionY);
        void changeRelationalPositionY(int relPosAddition);
        void changeRelationalPositionX(int relPosAddition);

        std::vector<int> getPlayerMapPosition();
        void setPlayerMapPosition(std::vector<int> position);
};

#endif