#include "CollisionDetector.h"

void CollisionDetector::playerResourceCollision(Player &player, Scene &scene) {

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

void CollisionDetector::playerUpperLeftResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int upperLeftRow = playerY/blockHeight;
    int upperLeftColumn = playerX/blockWidth;

    std::cout << "Upper Left: " << upperLeftRow << " " << upperLeftColumn << std::endl;

    // check if resource is there
    int blockInfo = scene.getSceneBlockInfo(upperLeftRow, upperLeftColumn);

    switch(blockInfo) {

        // 0 - space in scene is unoccupied
        // 1 - space in scene has obstacle
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste

        // regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

        case 2:
            player.setResource(0,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case 3:
            player.setResource(1,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case 4:
            player.setResource(2,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case 5:
            player.setResource(3,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case 6:
            player.setResource(4,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case 7:
            player.setResource(5,1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        default:
            break;
    }
}

void CollisionDetector::playerUpperRightResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int upperRightRow = playerY/blockHeight;
    int upperRightColumn = playerRight/blockWidth;

    // check if resource is there
    int blockInfo = scene.getSceneBlockInfo(upperRightRow, upperRightColumn);

    switch(blockInfo) {

        // 0 - space in scene is unoccupied
        // 1 - space in scene has obstacle
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste

        // regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

        case 2:
            player.setResource(0,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case 3:
            player.setResource(1,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case 4:
            player.setResource(2,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case 5:
            player.setResource(3,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case 6:
            player.setResource(4,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case 7:
            player.setResource(5,1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        default:
            break;
    }
}

void CollisionDetector::playerBottomLeftResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int bottomLeftRow = playerBottom/blockHeight;
    int bottomLeftColumn = playerX/blockWidth;

    // check if resource is there
    int blockInfo = scene.getSceneBlockInfo(bottomLeftRow, bottomLeftColumn);

    switch(blockInfo) {

        // 0 - space in scene is unoccupied
        // 1 - space in scene has obstacle
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste

        // regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

        case 2:
            player.setResource(0,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case 3:
            player.setResource(1,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case 4:
            player.setResource(2,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case 5:
            player.setResource(3,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case 6:
            player.setResource(4,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case 7:
            player.setResource(5,1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        default:
            break;
    }
}

void CollisionDetector::playerBottomRightResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int bottomRightRow = playerBottom/blockHeight;
    int bottomRightColumn = playerRight/blockWidth;

    // check if resource is there
    int blockInfo = scene.getSceneBlockInfo(bottomRightRow, bottomRightColumn);

    switch(blockInfo) {

        // 0 - space in scene is unoccupied
        // 1 - space in scene has obstacle
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste

        // regular inventory: { scrap metal, rags, oil, power source, wire, nuclear waste }

        case 2:
            player.setResource(0,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case 3:
            player.setResource(1,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case 4:
            player.setResource(2,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case 5:
            player.setResource(3,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case 6:
            player.setResource(4,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case 7:
            player.setResource(5,1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        default:
            break;
    }
}



