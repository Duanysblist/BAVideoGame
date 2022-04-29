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
#include <array>
#include <random>
#include <time.h>

class Player {
    private:
        int positionX = 0;
        int positionY = 0;
        int screenLocation;
        int playerHealth = MAX_HEALTH;

        // For map position
        std::vector<int> playerMapPosition = std::vector<int>(2, 0);

        // inventories
        // regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }
        int inventory [6] = { 0,0,0,0,0,0 };
        // key inventory: { large power source, long wire, large nuclear waste }
        int key_inventory [3] = { 0,0,0 };

        bool crowbar = false;

        //directional bools
        bool upDir = false;
        bool leftDir = false;
        bool rightDir = true;
        bool downDir = false;

    public:

        int getResource(const int resourceType) const;
        void setResource(const int resourceType, const int amountToAdd);
        int getKeyResource(const int resourceType) const;
        void setKeyResource(const int resourceType);
        bool getCrowbar() const;
        void setCrowbar(const bool crowbarPossessed);
        int useMove(const int move);
        std::array<bool, 12> getPossibleBattleMoves() const;

        int getPlayerHealth() const;
        void setPlayerHealth(int newHealth);
        void changePlayerHealth(int healthAddition);

        int getPlayerScreenPositionX() const;
        int getPlayerScreenPositionY() const;
        void changePlayerScreenPosition(const int changeX, const int changeY);
        void setPlayerScreenPosition(const int newX, const int newY);
        void limitPlayerScreenPosition();
        int checkIfPlayerIsAtScreenBoundary() const;

        void playerMoveUp(const int dt);
        void playerMoveDown(const int dt);
        void playerMoveLeft(const int dt);
        void playerMoveRight(const int dt);

        std::array<bool, 2> getDirections() const;

        std::vector<int> getPlayerMapPosition() const;
        void setPlayerMapPosition(std::vector<int> position);
};

#endif