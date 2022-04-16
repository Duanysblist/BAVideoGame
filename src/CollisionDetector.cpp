#include "CollisionDetector.h"

void CollisionDetector::playerResourceCollision(const Player &player, const Scene &scene) {

    playerX = player.getPlayerScreenPositionX();
    playerY = player.getPlayerScreenPositionY();

    playerRight = playerX + PLAYER_WIDTH;
    playerBottom = playerY + PLAYER_HEIGHT;

    blockHeight = SCREEN_HEIGHT/scene.getSceneRows();
    blockWidth = SCREEN_WIDTH/scene.getSceneColumns();

    playerUpperLeftResourceCollision(player, scene);
    playerUpperRightResourceCollision(player, scene);
    playerBottomLeftResourceCollision(player, scene);
    playerBottomRightResourceCollision(player, scene);
}

void CollisionDetector::playerUpperLeftResourceCollision(const Player &player, const Scene &scene) const {

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    
}