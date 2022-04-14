#include "bionic_apocalypse_renderer.h"

void Renderer::csci437_error(const std::string& msg) const {
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void Renderer::csci437_img_error(const std::string& msg) const {
    std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
    exit(0);
}

void Renderer::csci437_ttf_error(const std::string& msg) const {
    std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
    exit(0);
}
 
void Renderer::window_startup() {
	/*** Initialization ***/

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) csci437_error("SDL could not initialize!");

    // Create window
    window = SDL_CreateWindow("Bionic Apocalypse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) csci437_error("Window could not be created!");

    // Init Bitmap loading
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) csci437_img_error("SDL could not initialize bitmap loaders!");

    // init TTF
    if (TTF_Init() < 0) csci437_ttf_error("Unable to initialize TTF!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) csci437_error("Unable to create renderer!");


    font = TTF_OpenFont("../resource/Arial.ttf", 18);
    if (font == NULL) csci437_error("Unable to open font!");


    drawObstacles();


}

void Renderer::window_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::drawPlayer(const Player &player, const bool &world) {
    SDL_Surface* image = IMG_Load("../resource/player_texture.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (player_texture == NULL) csci437_error("Could not create texture from surface!");

    if (world) {
        player_rect = { player.getPlayerScreenPositionX(), player.getPlayerScreenPositionY(), 100, 100 };
        SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }
    else {
        player_rect = {0, 500, 100, 100};
        SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }

    SDL_DestroyTexture(player_texture);
    // delete image
    SDL_FreeSurface( image );
    image = NULL;
}

void Renderer::drawEnemy(const int &posX, const int &posY) {
    image = IMG_Load("../resource/enemy_texture.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* enemy_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (enemy_texture == NULL) csci437_error("Could not create texture from surface!");

    enemy_rect = { posX, posY, ENEMY_WIDTH, ENEMY_HEIGHT };
    SDL_RenderCopyEx(renderer, enemy_texture, NULL, &enemy_rect, 0, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(enemy_texture);
}

bool Renderer::checkCollision(SDL_Rect a, SDL_Rect b){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool Renderer::checkPlayerEnemyCollision() {
    return checkCollision(player_rect, enemy_rect);
}

// Need a drawObstacles function
// Can use the player_rect and enemy_rect from this class to check collision detection
// Should randomly generate rects on the screen
void Renderer::drawObstacles() {
    // First step: draw a single rect in a random position on screen that the enemy and player cannot cross
    // Get coordinates to place obstacle at

    //TODO: This should go in a collectObstacles function
    // Need to draw an obstacle for each 1 in the 10x16 matrix
    // Create a for loop and check for obstacles in the scene
        // If a value of 1 is found in the matrix
            // obstacle_x_coord = 80 * j
            // obstacle_y_coord = 70 * i
            // Create a rect for that obstacle
                // obstacle_rect = {obstacle_x_coord, obstacle_y_coord, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
            // Add that obstacle to an arrayto draw once finished
            // obstacle_arr[counter] = obstacle_rect
    
    // TODO: This should go in the drawObstacles(SDL_Rect [] obstacles) function
    // Once the loop is finished and all obstacle rects have been made
        // Render the obstacle rects to the screen
        // SDL_RenderCopyEx(renderer, obstacle_texture, NULL, &obstacle_arr[i], 0, NULL, SDL_FLIP_NONE);



    // Random coordinates on the screen
    // const int obstacle_x_coord = 500;
    // const int obstacle_y_coord = 500;
    // Need to check these coordinates against the range that the player and enemy take up
    // Create a rect out of the parts of the obstacle
    // SDL_Rect obstacle_rect = {obstacle_x_coord, obstacle_y_coord, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
    

    // Check for collisions between the obstacle and the player/enemy
    // If there is a collision, recalculate the coordinates of the obstacle until there is no collision
    // while(checkCollision(player_rect, obstacle_rect) || checkCollision(enemy_rect, obstacle_rect)){
    //     obstacle_x_coord = (rand() % SCREEN_WIDTH) + OBSTACLE_WIDTH;
    //     obstacle_y_coord = (rand() % (SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT)) + OBSTACLE_HEIGHT;
    // }
    // If there are no collisions, draw the obstacle to the screen
    // SDL_Surface* obstacle_image = IMG_Load("../resource/generic_key_resource.png");
    // if (obstacle_image == NULL) csci437_img_error("Could not create image!");
    // SDL_Texture* obstacle_texture = SDL_CreateTextureFromSurface(renderer, obstacle_image);
    // if (obstacle_texture == NULL) csci437_error("Could not create texture from surface!");
    // SDL_RenderCopyEx(renderer, obstacle_texture, NULL, &obstacle_rect, 0, NULL, SDL_FLIP_NONE);

}

void Renderer::drawText(const char* words, const int dst_x, const int dst_y, const int r, const int g, const int b) {
    SDL_Surface* text = TTF_RenderText_Solid( font, words, color );
    if ( text == NULL ) csci437_ttf_error("Unable to render text!");
    texture = SDL_CreateTextureFromSurface( renderer, text );
    if(texture == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect dst = { dst_x, dst_y, text->w, text->h};
    SDL_Point rot = {text->w/2, text->h/2};
    SDL_SetTextureColorMod( texture, r, g, b );
    SDL_RenderCopyEx( renderer, texture, NULL, &dst, 0, &rot, SDL_FLIP_NONE );
    SDL_DestroyTexture(texture);
    // free surface
    SDL_FreeSurface( text );
    text = NULL;
}

void Renderer::drawHealthBar(const Player &player) {
    double player_health = player.getPlayerHealth();
    double health_length = (player_health/MAX_HEALTH)*BAR_LENGTH;
    // outline of bar
    rectangleRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + BAR_LENGTH, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 255, 255, 255);
    // interior bar representing health
    boxRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + health_length, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 0, 0, 128);
    // write health under bar
    drawText("Health: ", BAR_START + 50, SCREEN_HEIGHT - 30, 255, 255, 255);
    int health = trunc(player_health);
    drawText((std::to_string(health)).c_str(), BAR_START + 120, SCREEN_HEIGHT - 30, 255, 255, 255);
}

void Renderer::drawInventory(const Player &player) {
    int IMAGE_WIDTH = 40;
    int IMAGE_HEIGHT = 40;
    int RELATIVE_X0 = BAR_START + BAR_LENGTH + 60;
    int RELATIVE_Y0 = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT + ((BOTTOM_BAR_HEIGHT-IMAGE_HEIGHT)/2);
    int GAP_BTW_IMAGES = 120;
    // draw resource pics
    // scrap metal
    SDL_Surface* image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scrap_metal = SDL_CreateTextureFromSurface(renderer, image);
    if (scrap_metal == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect scrap_metal_rect = { RELATIVE_X0, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, scrap_metal, NULL, &scrap_metal_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(scrap_metal);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // rags
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* rags = SDL_CreateTextureFromSurface(renderer, image);
    if (rags == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect rags_rect = { RELATIVE_X0 + GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, rags, NULL, &rags_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(rags);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // oil
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* oil = SDL_CreateTextureFromSurface(renderer, image);
    if (oil == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect oil_rect = { RELATIVE_X0 + 2*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, oil, NULL, &oil_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(oil);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // power sources
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* power_source = SDL_CreateTextureFromSurface(renderer, image);
    if (power_source == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect power_source_rect = { RELATIVE_X0 + 3*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, power_source, NULL, &power_source_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(power_source);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // wire
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* wire = SDL_CreateTextureFromSurface(renderer, image);
    if (wire == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect wire_rect = { RELATIVE_X0 + 4*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, wire, NULL, &wire_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(wire);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // nuclear waste
    image = IMG_Load("../resource/generic_resource.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* nuclear_waste = SDL_CreateTextureFromSurface(renderer, image);
    if (nuclear_waste == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect nuclear_waste_rect = { RELATIVE_X0 + 5*GAP_BTW_IMAGES, RELATIVE_Y0, IMAGE_WIDTH, IMAGE_HEIGHT };
    SDL_RenderCopyEx(renderer, nuclear_waste, NULL, &nuclear_waste_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(nuclear_waste);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // write quantity
    // scrap metal
    drawText(":", RELATIVE_X0 + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    int quantity = player.getResource(0);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // rags
    drawText(":", RELATIVE_X0 + (GAP_BTW_IMAGES) + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(1);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + (GAP_BTW_IMAGES) + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // oil
    drawText(":", RELATIVE_X0 + 2*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(2);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 2*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // power sources
    drawText(":", RELATIVE_X0 + 3*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(3);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 3*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // wire
    drawText(":", RELATIVE_X0 + 4*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(4);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 4*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // nuclear waste
    drawText(":", RELATIVE_X0 + 5*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(5);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 5*(GAP_BTW_IMAGES) + IMAGE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
}

void Renderer::drawKeyInventory(const Player &player) {
    // image of resource will appear if owned by the player. otherwise, will be empty box
    // draw outlines of three boxes
    int END_X = SCREEN_WIDTH - 60;
    int BOX_HEIGHT = 50;
    int BOX_WIDTH = BOX_HEIGHT;
    int RELATIVE_Y0 = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT + ((BOTTOM_BAR_HEIGHT-BOX_HEIGHT)/2) + 10;
    rectangleRGBA(renderer, END_X - 3*BOX_WIDTH, RELATIVE_Y0, END_X - 2*BOX_WIDTH, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);
    rectangleRGBA(renderer, END_X - 2*BOX_WIDTH, RELATIVE_Y0, END_X - BOX_WIDTH, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);
    rectangleRGBA(renderer, END_X - BOX_WIDTH, RELATIVE_Y0, END_X, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);
    // write header text
    drawText("KEY RESOURCES", END_X - 150, RELATIVE_Y0 - 25, 255, 255, 255);
    // draw resources if owned by player
    if (player.getKeyResource(0) == 1) {
        SDL_Surface* image = IMG_Load("../resource/generic_key_resource.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key1 = SDL_CreateTextureFromSurface(renderer, image);
        if (key1 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key1_rect = { END_X - 3*BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, key1, NULL, &key1_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key1);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
    if (player.getKeyResource(1) == 1) {
        SDL_Surface* image = IMG_Load("../resource/generic_key_resource.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key2 = SDL_CreateTextureFromSurface(renderer, image);
        if (key2 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key2_rect = { END_X - 2*BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, key2, NULL, &key2_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key2);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
    if (player.getKeyResource(2) == 1) {
        SDL_Surface* image = IMG_Load("../resource/generic_key_resource.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key3 = SDL_CreateTextureFromSurface(renderer, image);
        if (key3 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key3_rect = { END_X - BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, key3, NULL, &key3_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key3);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
}

void Renderer::drawBattleUI(const Player &player) {
    std::array<bool, 12> moves = player.getPossibleBattleMoves();
    
    int RELATIVE_X0 = 100;
    int RELATIVE_Y0 = 100;
    int ACTION_BOX_WIDTH = 250;
    int ACTION_BOX_HEIGHT = 30;
    int LEFT_BORDER = 25;
    int VERTICAL_SPACING = 10;
    int PREV_BOX_HEIGHT = ACTION_BOX_HEIGHT + VERTICAL_SPACING;
    int BACKGROUND_WIDTH = 3*LEFT_BORDER + 2*ACTION_BOX_WIDTH;
    int BACKGROUND_HEIGHT = VERTICAL_SPACING + 6*PREV_BOX_HEIGHT;

    // CURRENT COLORS ARE JUST PLACEHOLDERS -- CAN BE CHANGED
    // background rectangle
    boxRGBA(renderer, RELATIVE_X0, RELATIVE_Y0, RELATIVE_X0 + BACKGROUND_WIDTH, RELATIVE_Y0 + BACKGROUND_HEIGHT, 255, 210, 210, 255);
    // action backgrounds
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);

    
    if (moves[0]) {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Heal Player", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 133, 125, 125);
        drawText("Heal Player", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 133, 125, 125);
    }
    
    if (moves[1]) {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[2]) {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[3]) {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Armor Plate", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Armor Plate", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[4]) {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Time Bomb", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Time Bomb", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[5]) {
        drawText("6", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Trip Enemy", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("6", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Trip Enemy", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[6]) {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 133, 125, 125);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 133, 125, 125);
    }

    if (moves[7]) {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 133, 125, 125);
    }

    if (moves[8]) {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Block Attack", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Block Attack", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
    }

    if (moves[9]) {
        drawText("10", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("10", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
    }

    if (moves[10]) {
        drawText("11", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Crowbar", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("11", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Electric Crowbar", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
    }

    if (moves[11]) {
        drawText("12", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("12", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 133, 125, 125);
    }

}

void Renderer::drawResources(const Scene &scene) {
    int** layout = scene.getSceneLayout();
    const int numRows = scene.getSceneRows();
    const int numColumns = scene.getSceneColumns();

    const int screenBlockWidth = SCREEN_WIDTH/numColumns;
    const int screenBlockHeight = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/numRows;

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++) {
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste
            if (layout[i][j] == 2) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            } else if (layout[i][j] == 3) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            } else if (layout[i][j] == 4) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            } else if (layout[i][j] == 5) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            } else if (layout[i][j] == 6) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            } else if (layout[i][j] == 7) {
                boxRGBA(renderer, j*screenBlockWidth, i*screenBlockHeight, j*screenBlockWidth + screenBlockWidth, i*screenBlockHeight + screenBlockHeight, 255, 200, 0, 128);
            }
        }
    }
}

void Renderer::window_update(const Player &player, const bool &world, Scene &scene) {
    if (world) {
        // Draw line for bottom bar
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar(player);
        drawInventory(player);
        drawKeyInventory(player);

        drawResources(scene);

        SDL_RenderPresent(renderer);
    }
    else {
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar(player);
        drawInventory(player);
        drawKeyInventory(player);

        drawBattleUI(player);
        SDL_RenderPresent(renderer);
    }
}



