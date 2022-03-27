#include "bionic_apocalypse_enemy.h"

#ifndef BIONIC_APOCALYPSE_SCENE_H
#define BIONIC_APOCALYPSE_SCENE_H

class Scene(int sceneNum, int[][] sceneLayout, int[][] loadingZones, int[][] resourceLocations, Enemy[] enemies) {

    public:
        void addEnemy(Enemy newEnemy);
        void renderEnemies();
        void setSceneNumber(int num);
        void update();
        void draw();

};

#endif