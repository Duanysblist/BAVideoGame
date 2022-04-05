
#include "bionic_apocalypse_constants.h"
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

   public:
   int getSceneID();
   void setSceneID(int num);
   int getsceneCategoryID();
   void setSceneCategoryID(int num);
   int** getSceneLayout();
   void setSceneLayout(int**);
   Scene() {
       sceneID = -1;
       sceneCategoryID = -1;
   }
   Scene(int id, int catID) {
       sceneID = id;
       sceneCategoryID = catID;
   }
};