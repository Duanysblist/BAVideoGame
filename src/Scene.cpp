#include "Scene.h"

int Scene::getSceneID() const {
    return sceneID;
}

void Scene::setSceneID(const int ID) {
    this->sceneID = ID;
}

int Scene::getsceneCategoryID() const {
    return sceneCategoryID;
}

void Scene::setSceneCategoryID(const int catID) {
    this->sceneCategoryID = catID;
}

int Scene::getSceneRows() const {
    return rows;
}

int Scene::getSceneColumns() const {
    return columns;
}

void Scene::createSceneLayout(const int numRows, const int numColumns){
    /**
        0 - space in scene is unoccupied

        1 - space in scene has obstacle

        2 - space in scene has scrap metal
        3 - space in scene has rags
        4 - space in scene has oil
        5 - space in scene has power source
        6 - space in scene has wire
        7 - space in scene has nuclear waste

        8 - space in scene has key resource power source
        9 - space in scene has key resource wire
        10 - space in scene has key resource nuclear waste
    **/
    layout = new int*[numRows];
    for(int i = 0; i < numRows; i++) {
        layout[i] = new int[numColumns];
        for(int j = 0; j < numColumns; j++) {
            // for now just randomly choosing if a space has an obstacle or resource
            /** 1-4 obstacle
                9-34, 41-60 nothing
                35 scrap metal
                36 rags
                37 oil
                38 power source
                39 wire
                40 nuclear waste
            **/
            int random = rand() % 60 + 1;
            if(random <= 4){
                layout[i][j] = 1; // obstacle
            } else if (5 <= random && random <= 34 || random > 40) {
                layout[i][j] = 0; // nothing
            } else if (random == 35) {
                layout[i][j] = 2; // scrap metal
            } else if (random == 36) {
                layout[i][j] = 3; // rags
            } else if (random == 37) {
                layout[i][j] = 4; // oil
            } else if (random == 38) {
                layout[i][j] = 5; // power source
            } else if (random == 39) {
                layout[i][j] = 6; // wire
            }
            else {layout[i][j] = 7;} // nuclear waste
        }
    }
}

// For map of obstacles in a scene
int** Scene::getSceneLayout() const {
    return layout;
}

int Scene::getSceneBlockInfo(int row, int col) const {
    return layout[row][col];
}

void Scene::setSceneBlockInfo(int row, int col, int val) {
    layout[row][col] = val;
}

void Scene::freeSceneLayout(int** matrix, const int numRows){
    if(matrix){
        for(int i = 0; i < numRows; i++) { if(matrix[i]){ delete[] matrix[i]; } }
        delete[] matrix;
    }
} 

void Scene::setSceneLayout(int** prefLayout) {
    this->layout = prefLayout;
}