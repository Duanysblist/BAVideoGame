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

// For map of obstacles in a scene
int** Scene::getSceneLayout() {
    return layout;
}

void Scene::setSceneLayout(int** prefLayout) {
    this->layout = prefLayout;
}