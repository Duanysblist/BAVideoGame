#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_enemy.h"
#include "Scene.h"
#include "bionic_apocalypse_constants.h"


/** 
    collision detector code only works as long as 
    each screen "block" width is at least half of the player's width
    and each screen "block" height is at least half of the player's height
**/

class CollisionDetector {


private:
    int playerX;
    int playerY;

    int playerRight;
    int playerBottom;

    int blockHeight;
    int blockWidth;

    int numRows;
    int numCols;

    void playerUpperLeftResourceCollision(Player &player, Scene &scene) const;
    void playerUpperRightResourceCollision(Player &player, Scene &scene) const;
    void playerBottomLeftResourceCollision(Player &player, Scene &scene) const;
    void playerBottomRightResourceCollision(Player &player, Scene &scene) const;
    void playerCenterResourceCollision(Player &player, Scene &scene) const;
    bool playerUpperLeftWallCollision(Player &player, Scene &scene);
    bool playerUpperRightWallCollision(Player &player, Scene &scene);
    bool playerBottomLeftWallCollision(Player &player, Scene &scene);
    bool playerBottomRightWallCollision(Player &player, Scene &scene);

    void fixLimits(int &row, int &col) const;

public:
    void playerResourceCollision(Player &player, Scene &scene);
    bool playerEnemyCollision(Player &player, Enemy &enemy) const;
    int playerWallCollision(Player &player, Scene &scene);
};

#endif