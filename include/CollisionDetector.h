#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "bionic_apocalypse_player.h"
#include "Scene.h"

class CollisionDetector {

public:
    bool playerResourceCollision(const Player &player, const Scene &scene) const;

};

#endif