#include "Scene.h"
#include <cstdlib>

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

int** Scene::createSceneLayout(int numRows, int numColumns){
    layout = new int*[numRows];
    for(int i = 0; i < numRows; i++) {
        layout[i] = new int[numColumns];
        for(int j = 0; j < numColumns; j++) {
            // for now just randomly choosing if a space has an obstacle
            int random = rand() % 2 + 1;
            if(random == 1){
                layout[i][j] = 1;
            } else {
                layout[i][j] = 0;
            }
            
        }
    }
    return layout;
}

// For map of obstacles in a scene
int** Scene::getSceneLayout() {
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