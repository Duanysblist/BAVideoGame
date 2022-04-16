
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
   int rows = 10;
   int columns = 16;

   public:
   int getSceneID() const;
   void setSceneID(const int num);
   int getsceneCategoryID() const;
   void setSceneCategoryID(const int num);
   int getSceneRows() const;
   int getSceneColumns() const;
   int** createSceneLayout(const int rows, const int columns);
   int** getSceneLayout() const;
   void setSceneLayout(int**);
   void freeSceneLayout(int** layout, const int rows);
   int getSceneBlockInfo(int row, int col) const;
   void setSceneBlockInfo(int row, int col, int val);
   Scene() {
       sceneID = -1;
       sceneCategoryID = -1;
   }
   Scene(const int id, const int catID) {
       sceneID = id;
       sceneCategoryID = catID;
   }
};

#endif