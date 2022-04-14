#include "Scene.h"

int Scene::getSceneID(){
    return sceneID;
}

void Scene::setSceneID(int ID) {
    this->sceneID = ID;
}

int Scene::getsceneCategoryID() {
    return sceneCategoryID;
}

void Scene::setSceneCategoryID(int catID) {
    this->sceneCategoryID = catID;
}

int Scene::getSceneRows() const {
    return rows;
}

int Scene::getSceneColumns() const {
    return columns;
}

int** Scene::createSceneLayout(int numRows, int numColumns){
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
            /** 1-5 obstacle
                6-14 nothing
                15 scrap metal
                16 rags
                17 oil
                18 power source
                19 wire
                20 nuclear waste
            **/
            int random = rand() % 20 + 1;
            if(random <= 5){
                layout[i][j] = 1; // obstacle
            } else if (6 <= random && random <= 14) {
                layout[i][j] = 0; // nothing
            } else if (random == 15) {
                layout[i][j] = 2; // scrap metal
            } else if (random == 16) {
                layout[i][j] = 3; // rags
            } else if (random == 17) {
                layout[i][j] = 4; // oil
            } else if (random == 18) {
                layout[i][j] = 5; // power source
            } else if (random == 19) {
                layout[i][j] = 6; // wire
            }
            else {layout[i][j] = 7;} // nuclear waste
        }
    }
    return layout;
}

// For map of obstacles in a scene
int** Scene::getSceneLayout() const {
    return layout;
}

void Scene::freeSceneLayout(int** matrix, int numRows){
    if(matrix){
        for(int i = 0; i < numRows; i++) { if(matrix[i]){ delete[] matrix[i]; } }
        delete[] matrix;
    }
} 

void Scene::setSceneLayout(int** prefLayout) {
    this->layout = prefLayout;
}