#include "CollisionDetector.h"

void CollisionDetector::fixLimits(int &row, int &col) const {
    if (row < 0) {
        row = 0;
    } else if (row > (numRows - 1)) {
        row = numRows - 1;
    }
    if (col < 0) {
        col = 0;
    } else if (col > (numCols - 1)) {
        col = numCols - 1;
    }
}

void CollisionDetector::playerResourceCollision(Player &player, Scene &scene) {

    playerX = player.getPlayerScreenPositionX();
    playerY = player.getPlayerScreenPositionY();

    playerRight = playerX + PLAYER_WIDTH;
    playerBottom = playerY + PLAYER_HEIGHT;

    numRows = scene.getSceneRows();
    numCols = scene.getSceneColumns();

    blockHeight = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/numRows;
    blockWidth = SCREEN_WIDTH/numCols;

    playerUpperLeftResourceCollision(player, scene);
    playerUpperRightResourceCollision(player, scene);
    playerBottomLeftResourceCollision(player, scene);
    playerBottomRightResourceCollision(player, scene);
    playerCenterResourceCollision(player, scene);
}

void CollisionDetector::playerUpperLeftResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int upperLeftRow = playerY/blockHeight;
    int upperLeftColumn = playerX/blockWidth;

    fixLimits(upperLeftRow, upperLeftColumn);

    // std::cout << "Upper Left: " << upperLeftRow << " " << upperLeftColumn << std::endl;

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

    // upper right coordinates are playerRight, playerY

    // find out which block the player's upper right corner is in
    // int division truncates towards zero so this should work
    int upperRightRow = playerY/blockHeight;
    int upperRightColumn = playerRight/blockWidth;

    fixLimits(upperRightRow, upperRightColumn);

    // std::cout << "Upper Right: " << upperRightRow << " " << upperRightColumn << std::endl;

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

    // bottom left coordinates are playerX, playerBottom

    // find out which block the player's bottom left corner is in
    // int division truncates towards zero so this should work
    int bottomLeftRow = playerBottom/blockHeight;
    int bottomLeftColumn = playerX/blockWidth;

    // std::cout << "Bottom Left: " << bottomLeftRow << " " << bottomLeftColumn << std::endl;

    fixLimits(bottomLeftRow, bottomLeftColumn);

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

    // bottom right coordinates are playerRight, playerBottom

    // find out which block the player's bottom right corner is in
    // int division truncates towards zero so this should work
    int bottomRightRow = playerBottom/blockHeight;
    int bottomRightColumn = playerRight/blockWidth;

    fixLimits(bottomRightRow, bottomRightColumn);

    // std::cout << "Bottom Right: " << bottomRightRow << " " << bottomRightColumn << std::endl;

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

void CollisionDetector::playerCenterResourceCollision(Player &player, Scene &scene) const {

    int centerX = playerX + (PLAYER_WIDTH/2);
    int centerY = playerY + (PLAYER_HEIGHT/2);

    // find out which block the player's center is in
    // int division truncates towards zero so this should work
    int centerRow = centerY/blockHeight;
    int centerColumn = centerX/blockWidth;

    fixLimits(centerRow, centerColumn);

    // std::cout << "Center: " << centerRow << " " << centerColumn << std::endl;

    // check if resource is there
    int blockInfo = scene.getSceneBlockInfo(centerRow, centerColumn);

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
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        case 3:
            player.setResource(1,1);
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        case 4:
            player.setResource(2,1);
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        case 5:
            player.setResource(3,1);
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        case 6:
            player.setResource(4,1);
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        case 7:
            player.setResource(5,1);
            scene.setSceneBlockInfo(centerRow, centerColumn, 0);
            break;
        default:
            break;
    }

}

