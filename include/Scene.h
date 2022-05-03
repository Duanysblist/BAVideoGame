
#ifndef SCENE_H
#define SCENE_H

#include "bionic_apocalypse_constants.h"
#include <cstdlib>
class Scene {

    /*
        What does a scene need?

            Background image
            sceneId
            sceneCategoryId
            2D array where the obstacles are in the scene

    */
    private:
        int sceneID;
        int sceneCategoryID;
        int** layout;
        int rows;
        int columns;
        
        // scene zone information
        // 0 - in the tutorial zone
        // 1 - in the power source zone
        // 2 - in the wires zone
        // 3 - in the nuclear waste zone
        int sceneZone;

    public:
        int getSceneZone() const;
        void setSceneZone(const int zone);

        int getSceneID() const;
        void setSceneID(const int num);
        int getsceneCategoryID() const;
        void setSceneCategoryID(const int num);
        int getSceneRows() const;
        int getSceneColumns() const;
        void createSceneLayout(const int rows, const int columns);
        int** getSceneLayout() const;
        // void setSceneLayout(int**);
        void setSceneLayout(int[][18]);
        void freeSceneLayout(int** layout, const int rows);
        int getSceneBlockInfo(int row, int col) const;
        void setSceneBlockInfo(int row, int col, int val);
        Scene() {
            sceneID = -1;
            sceneCategoryID = -1;
            sceneZone = 0;
            rows = 10;
            columns = 18;
        }
        Scene(const int id, const int catID, const int zone, const int r, const int c) {
            sceneID = id;
            sceneCategoryID = catID;
            sceneZone = zone;
            rows = r;
            columns = c;
        }

        void distributeResources(); 
        int* covertScenePosToPixels(int x, int y);
};

#endif