#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "bionic_apocalypse_player.h"
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


    void playerUpperLeftResourceCollision(const Player &player, const Scene &scene) const;
    void playerUpperRightResourceCollision(const Player &player, const Scene &scene) const;
    void playerBottomLeftResourceCollision(const Player &player, const Scene &scene) const;
    void playerBottomRightResourceCollision(const Player &player, const Scene &scene) const;

public:
    void playerResourceCollision(const Player &player, const Scene &scene);

};

#endif