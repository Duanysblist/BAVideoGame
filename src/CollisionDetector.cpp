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
}

void CollisionDetector::playerUpperLeftResourceCollision(Player &player, Scene &scene) const {

    // upper left coordinates are playerX, playerY

    // find out which block the player's upper left corner is in
    // int division truncates towards zero so this should work
    int upperLeftRow = playerY/blockHeight;
    int upperLeftColumn = playerX/blockWidth;

    fixLimits(upperLeftRow, upperLeftColumn);

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
        case CROWBAR:
            player.setCrowbar(true);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case KEY_POWER:
            player.setKeyResource(0);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case KEY_WIRE:
            player.setKeyResource(1);
            scene.setSceneBlockInfo(upperLeftRow, upperLeftColumn, 0);
            break;
        case KEY_NUCLEAR:
            player.setKeyResource(2);
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
        case CROWBAR:
            player.setCrowbar(true);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case KEY_POWER:
            player.setKeyResource(0);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case KEY_WIRE:
            player.setKeyResource(1);
            scene.setSceneBlockInfo(upperRightRow, upperRightColumn, 0);
            break;
        case KEY_NUCLEAR:
            player.setKeyResource(2);
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
        case CROWBAR:
            player.setCrowbar(true);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case KEY_POWER:
            player.setKeyResource(0);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case KEY_WIRE:
            player.setKeyResource(1);
            scene.setSceneBlockInfo(bottomLeftRow, bottomLeftColumn, 0);
            break;
        case KEY_NUCLEAR:
            player.setKeyResource(2);
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
        case CROWBAR:
            player.setCrowbar(true);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case KEY_POWER:
            player.setKeyResource(0);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case KEY_WIRE:
            player.setKeyResource(1);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        case KEY_NUCLEAR:
            player.setKeyResource(2);
            scene.setSceneBlockInfo(bottomRightRow, bottomRightColumn, 0);
            break;
        default:
            break;
    }
}

bool CollisionDetector::playerEnemyCollision(Player &player, Enemy &enemy) const {

    //The sides of the entities
    int leftPlayer, leftEnemy;
    int rightPlayer, rightEnemy;
    int topPlayer, topEnemy;
    int bottomPlayer, bottomEnemy;

    //Calculate the sides of rect A
    leftPlayer = player.getPlayerScreenPositionX();
    rightPlayer = leftPlayer + PLAYER_WIDTH;
    topPlayer = player.getPlayerScreenPositionY();
    bottomPlayer = topPlayer + PLAYER_HEIGHT;

    //Calculate the sides of rect B
    leftEnemy = enemy.getX();
    rightEnemy = leftEnemy + ENEMY_WIDTH;
    topEnemy = enemy.getY();
    bottomEnemy = topEnemy + ENEMY_HEIGHT;

    //If any of the sides from A are outside of B
    if( bottomPlayer <= topEnemy )
    {
        return false;
    }

    if( topPlayer >= bottomEnemy )
    {
        return false;
    }

    if( rightPlayer <= leftEnemy )
    {
        return false;
    }

    if( leftPlayer >= rightEnemy )
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}

int CollisionDetector::playerWallCollision(Player &player, Scene &scene) {

    playerX = player.getPlayerScreenPositionX();
    playerY = player.getPlayerScreenPositionY();

    playerRight = playerX + PLAYER_WIDTH;
    playerBottom = playerY + PLAYER_HEIGHT;

    numRows = scene.getSceneRows();
    numCols = scene.getSceneColumns();

    blockHeight = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/numRows;
    blockWidth = SCREEN_WIDTH/numCols;

    if(playerUpperLeftWallCollision(player, scene)){
        return 1;
    }
    if(playerUpperRightWallCollision(player, scene)){
        return 2;
    }
    if(playerBottomLeftWallCollision(player, scene)){
        return 3;
    }
    if(playerBottomRightWallCollision(player, scene)){
        return 4;
    }

    return 0;
}

bool CollisionDetector::playerUpperLeftWallCollision(Player &player, Scene &scene){
    int upperLeftRow = playerY/blockHeight;
    int upperLeftColumn = playerX/blockWidth;

    fixLimits(upperLeftRow, upperLeftColumn);

    // check if wall is there
    int blockInfo = scene.getSceneBlockInfo(upperLeftRow, upperLeftColumn);
    if(blockInfo == 1){
        return true;
    }
    if((blockInfo > 10 && blockInfo < 30) || blockInfo > 31){
        return true;
    }
    return false;

}
bool CollisionDetector::playerUpperRightWallCollision(Player &player, Scene &scene){
    int upperRightRow = playerY/blockHeight;
    int upperRightColumn = playerRight/blockWidth;

    fixLimits(upperRightRow, upperRightColumn);

    // check if wall is there
    int blockInfo = scene.getSceneBlockInfo(upperRightRow, upperRightColumn);
    if(blockInfo == 1){
        return true;
    }
    if((blockInfo > 10 && blockInfo < 30) || blockInfo > 31){
        return true;
    }
    return false;
}
bool CollisionDetector::playerBottomLeftWallCollision(Player &player, Scene &scene){
    // bottom left coordinates are playerX, playerBottom

    // find out which block the player's bottom left corner is in
    // int division truncates towards zero so this should work
    int bottomLeftRow = playerBottom/blockHeight;
    int bottomLeftColumn = playerX/blockWidth;

    fixLimits(bottomLeftRow, bottomLeftColumn);

    // check if wall is there
    int blockInfo = scene.getSceneBlockInfo(bottomLeftRow, bottomLeftColumn);
    if(blockInfo == 1){
        return true;
    }
    if((blockInfo > 10 && blockInfo < 30) || blockInfo > 31){
        return true;
    }
    return false;

}
bool CollisionDetector::playerBottomRightWallCollision(Player &player, Scene &scene){
        // bottom right coordinates are playerRight, playerBottom

    // find out which block the player's bottom right corner is in
    // int division truncates towards zero so this should work
    int bottomRightRow = playerBottom/blockHeight;
    int bottomRightColumn = playerRight/blockWidth;

    fixLimits(bottomRightRow, bottomRightColumn);

    // check if wall is there
    int blockInfo = scene.getSceneBlockInfo(bottomRightRow, bottomRightColumn);
    if(blockInfo == 1){
        return true;
    }
    if((blockInfo > 10 && blockInfo < 30) || blockInfo > 31){
        return true;
    }
    return false;
}