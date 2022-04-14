
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
   int getSceneID();
   void setSceneID(int num);
   int getsceneCategoryID();
   void setSceneCategoryID(int num);
   int getSceneRows() const;
   int getSceneColumns() const;
   int** createSceneLayout(int rows, int columns);
   int** getSceneLayout() const;
   void setSceneLayout(int**);
   void freeSceneLayout(int** layout, int rows);
   Scene() {
       sceneID = -1;
       sceneCategoryID = -1;
   }
   Scene(int id, int catID) {
       sceneID = id;
       sceneCategoryID = catID;
   }
};

#endif