#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "bionic_apocalypse_constants.h"

class Obstacle{
    /*
    What does the Obstacle class need?
        int obstacleID;
        int xPosition;
        int yPosition;
        int width;
        int height;
        SDL_Suface* image;
        SDL_Texture* texture;
        SDL_Rect obstacle_rect;
    */
   public:
        int obstacleID;
        int xPosition;
        int yPosition;
        int width;
        int height;
        SDL_Suface* image;
        SDL_Texture* texture;
        SDL_Rect* obstacle_rect;
        Obstacle(int x, int y){
            xPosition = x;
            yPosition = y;
            width = OBSTACLE_WIDTH;
            height = OBSTACLE_HEIGHT;
            image = IMG_Load("../resource/generic_key_resource.png");
            if (obstacle_image == NULL) csci437_img_error("Could not create image!");
            texture = SDL_CreateTextureFromSurface(renderer, obstacle_image);
            if (obstacle_texture == NULL) csci437_error("Could not create texture from surface!");
            obstacle_rect = {xPosition, yPosition, width, height};
        }
}