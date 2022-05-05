#include "bionic_apocalypse_renderer.h"


// error messages for texture and text things
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

    // make non-resizable
    SDL_SetWindowResizable(window, SDL_FALSE);

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


}

// clear the renderer
void Renderer::window_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

// display cutscene
void Renderer::cutscene(const int num) {
    std::string fileLoc = "../resource/"+std::to_string(num)+".png";
    const char *c = fileLoc.c_str();
    image = IMG_Load(c);
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* cutscene_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (cutscene_texture == NULL) csci437_error("Could not create texture from surface!");

    SDL_RenderCopyEx(renderer, cutscene_texture, NULL, &cutscene_rect, 0, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(cutscene_texture);
    SDL_FreeSurface(image);
}

// draw player
void Renderer::drawPlayer(const Player &player, const bool &world) {
    // load and create player texture
    SDL_Surface* image;
    if (player.getWalkingAnim()) {
        image = IMG_Load("../resource/PlayerWalk.png");
        if (image == NULL) csci437_img_error("Could not create image!");
    }
    else {
        image = IMG_Load("../resource/Player.png");
        if (image == NULL) csci437_img_error("Could not create image!");
    }

    SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (player_texture == NULL) csci437_error("Could not create texture from surface!");

    // if not in a battle, display the player in its screen position
    if (world) {
        player_rect = { player.getPlayerScreenPositionX(), player.getPlayerScreenPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT };
        // set direction that player is facing based on the direction it is moving in
        if (player.getDirections()[1] == false) {
            SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
        }
        else {
            SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    // if in battle, display the player in the bottom left of the screen
    else {
        player_rect = {0, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT+PLAYER_HEIGHT), PLAYER_WIDTH, PLAYER_HEIGHT};
        SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }

    // destroy the player texture
    SDL_DestroyTexture(player_texture);
    // delete image
    SDL_FreeSurface( image );
    image = NULL;
}

// draw an enemy given its position
void Renderer::drawEnemy(const Enemy &enemy, const bool &gameState) {
    // load and create enemy texture
    if (enemy.getAlive()) {
        image = IMG_Load("../resource/Basic_Enemy.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* enemy_texture = SDL_CreateTextureFromSurface(renderer, image);
        if (enemy_texture == NULL) csci437_error("Could not create texture from surface!");

        // set the enemy position to the passed in parameter position
        enemy_rect = { enemy.getX(), enemy.getY(), ENEMY_WIDTH, ENEMY_HEIGHT };

        // add the enemy to the renderer
        if (enemy.getDirection()){
            SDL_RenderCopyEx(renderer, enemy_texture, NULL, &enemy_rect, 0, NULL, SDL_FLIP_NONE);
        }
        else {
            SDL_RenderCopyEx(renderer, enemy_texture, NULL, &enemy_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        // destroy the texture and free the image
        SDL_DestroyTexture(enemy_texture);
        SDL_FreeSurface(image);
        image = NULL;
        if (gameState == false) {
            // obtain enemy health and calculate what fraction of the bar should be filled
            // bar length
            int BAR_L = 150;
            // bar start
            int BAR_S = 900;
            double enemy_health = enemy.getHealth();
            double health_length = (enemy_health/enemy.getMaxHealth())*BAR_L;

            // interior bar representing health
            boxRGBA(renderer, BAR_S, 400, BAR_S + health_length, 425, 255, 0, 0, 255);
            // outline of bar
            rectangleRGBA(renderer, BAR_S, 400, BAR_S + BAR_L + 1, 426, 0, 0, 0, 255);
            
            // write health value under bar
            drawText("Enemy Health: ", BAR_S, 425, 0, 0, 0);
            // change health to an int instead of double
            int health = trunc(enemy_health);
            drawText((std::to_string(health)).c_str(), BAR_S + 130, 425, 0, 0, 0);
        }
    }
}

// write out messages of what happened in battle
void Renderer::drawBattleMessages(const std::string &message, const int &damage, const int &playerDam) {
    std::string mes = "You used ";
    std::string earlyMes = " and dealt ";
    std::string midMes = " damage!";
    std::string enemyEarlyMes = "Enemy dealt ";
    std::string endMes = " damage!";
    std::string playerMes = "";
    if (playerDam > 0) {
        playerMes = mes + message + earlyMes + std::to_string(playerDam) + midMes;
    }
    else {
        playerMes = mes + message;
    }
    std::string enemMes = enemyEarlyMes + std::to_string(-1 * damage) + endMes;
    int n = playerMes.length();
    char toCharArr[n + 1];
    strcpy(toCharArr, playerMes.c_str());
    drawText(toCharArr, 200, 500, 0, 0, 0);
    int t = enemMes.length();
    char toChar[t + 1];
    strcpy(toChar, enemMes.c_str());
    drawText(toChar, 900, 300, 0, 0, 0);
}

void Renderer::drawCantUseMove() {
    std::string mes = "You cannot use this move!";
    int n = mes.length();
    char toCharArr[n + 1];
    strcpy(toCharArr, mes.c_str());
    drawText(toCharArr, 700, 500, 0, 0, 0);
}

void Renderer::drawMap(const std::vector<int> pos) {
    SDL_Surface* image = IMG_Load("../resource/map.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* map = SDL_CreateTextureFromSurface(renderer, image);
    if (map == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // MAP_WIDTH and MAP_HEIGHT are constants from the constants.h file
    // center map on the screen
    int x1 = (SCREEN_WIDTH-MAP_WIDTH)/2;
    int y1 = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT-MAP_HEIGHT)/2;
    SDL_Rect rect = { x1, y1, MAP_WIDTH, MAP_HEIGHT };
    SDL_RenderCopyEx(renderer, map, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(map);
    // draw dot to represent player -- center it in the scene on the map
    int pos_x = pos.at(1);
    int pos_y = pos.at(0);
    int scene_height = MAP_HEIGHT/8;
    int scene_width = MAP_WIDTH/6;
    boxRGBA(renderer, x1 + scene_width*pos_x + scene_width/2 - 3, y1 + scene_height*pos_y + scene_height/2 - 3, x1 + scene_width*pos_x + scene_width/2 + 3, y1 + scene_height*pos_y + scene_height/2 + 3, 255, 255, 255, 255);
}

// helper method to draw text
// pass in the text (words), the position (dst_x and dst_y), and the desired color (r,g,b)
void Renderer::drawText(const char* words, const int dst_x, const int dst_y, const int r, const int g, const int b) {
    // create a surface and texture from the passed in text
    SDL_Surface* text = TTF_RenderText_Solid( font, words, color );
    if ( text == NULL ) csci437_ttf_error("Unable to render text!");
    texture = SDL_CreateTextureFromSurface( renderer, text );
    if(texture == NULL) csci437_error("Could not create texture from surface!");
    
    // set the position
    SDL_Rect dst = { dst_x, dst_y, text->w, text->h};
    SDL_Point rot = {text->w/2, text->h/2};
    // change the color
    SDL_SetTextureColorMod( texture, r, g, b );
    
    // add text to the renderer
    SDL_RenderCopyEx( renderer, texture, NULL, &dst, 0, &rot, SDL_FLIP_NONE );
    
    // destroy texture and free surface
    SDL_DestroyTexture(texture);
    SDL_FreeSurface( text );
    text = NULL;
}

// draw the player health bar
void Renderer::drawHealthBar(const Player &player) {
    // obtain player health and calculate what fraction of the bar should be filled
    double player_health = player.getPlayerHealth();
    double health_length = (player_health/MAX_HEALTH)*BAR_LENGTH;

    // outline of bar
    rectangleRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + BAR_LENGTH, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 255, 255, 255);
    // interior bar representing health
    boxRGBA(renderer, BAR_START, SCREEN_HEIGHT - (2*BOTTOM_BAR_HEIGHT/3), BAR_START + health_length, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT/3), 255, 0, 0, 128);
    
    // write health value under bar
    drawText("Health: ", BAR_START + 50, SCREEN_HEIGHT - 30, 255, 255, 255);
    // change health to an int instead of double
    int health = trunc(player_health);
    drawText((std::to_string(health)).c_str(), BAR_START + 120, SCREEN_HEIGHT - 30, 255, 255, 255);
}

// draw the player's inventory at the bottom of the screen
void Renderer::drawInventory(const Player &player) {
    // adjustable parameters for display (eg. where the inventory is located, image size, etc.)
    int RESOURCE_WIDTH = 40;
    int RESOURCE_HEIGHT = 40;
    int RELATIVE_X0 = BAR_START + BAR_LENGTH + 50;
    int RELATIVE_Y0 = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT + ((BOTTOM_BAR_HEIGHT-RESOURCE_HEIGHT)/2);
    int GAP_BTW_IMAGES = 120;

    // draw resource pics
    // scrap metal
    SDL_Surface* image = IMG_Load("../resource/metal.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scrap_metal = SDL_CreateTextureFromSurface(renderer, image);
    if (scrap_metal == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect scrap_metal_rect = { RELATIVE_X0, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, scrap_metal, NULL, &scrap_metal_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(scrap_metal);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // rags
    image = IMG_Load("../resource/rags.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* rags = SDL_CreateTextureFromSurface(renderer, image);
    if (rags == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect rags_rect = { RELATIVE_X0 + GAP_BTW_IMAGES, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, rags, NULL, &rags_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(rags);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // oil
    image = IMG_Load("../resource/oil.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* oil = SDL_CreateTextureFromSurface(renderer, image);
    if (oil == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect oil_rect = { RELATIVE_X0 + 2*GAP_BTW_IMAGES, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, oil, NULL, &oil_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(oil);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // power sources
    image = IMG_Load("../resource/power.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* power_source = SDL_CreateTextureFromSurface(renderer, image);
    if (power_source == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect power_source_rect = { RELATIVE_X0 + 3*GAP_BTW_IMAGES, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, power_source, NULL, &power_source_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(power_source);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // wire
    image = IMG_Load("../resource/wire.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* wire = SDL_CreateTextureFromSurface(renderer, image);
    if (wire == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect wire_rect = { RELATIVE_X0 + 4*GAP_BTW_IMAGES, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, wire, NULL, &wire_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(wire);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // nuclear waste
    image = IMG_Load("../resource/nuclear.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* nuclear_waste = SDL_CreateTextureFromSurface(renderer, image);
    if (nuclear_waste == NULL) csci437_error("Could not create texture from surface!");
    SDL_Rect nuclear_waste_rect = { RELATIVE_X0 + 5*GAP_BTW_IMAGES, RELATIVE_Y0, RESOURCE_WIDTH, RESOURCE_HEIGHT };
    SDL_RenderCopyEx(renderer, nuclear_waste, NULL, &nuclear_waste_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(nuclear_waste);
    // free surface
    SDL_FreeSurface( image );
    image = NULL;

    // write quantity of each resource
    // scrap metal
    drawText(":", RELATIVE_X0 + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    int quantity = player.getResource(0);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // rags
    drawText(":", RELATIVE_X0 + (GAP_BTW_IMAGES) + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(1);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + (GAP_BTW_IMAGES) + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // oil
    drawText(":", RELATIVE_X0 + 2*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(2);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 2*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // power sources
    drawText(":", RELATIVE_X0 + 3*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(3);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 3*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // wire
    drawText(":", RELATIVE_X0 + 4*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(4);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 4*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
    // nuclear waste
    drawText(":", RELATIVE_X0 + 5*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 10, RELATIVE_Y0 + 10, 255, 255, 255);
    quantity = player.getResource(5);
    drawText((std::to_string(quantity)).c_str(), RELATIVE_X0 + 5*(GAP_BTW_IMAGES) + RESOURCE_WIDTH + 18, RELATIVE_Y0 + 10, 255, 255, 255);
}

void Renderer::drawKeyInventory(const Player &player) {
    // image of resource will appear if owned by the player. otherwise, will be empty box
    
    // draw outlines of three boxes
    // adjustable parameters for what the inventory looks like
    int END_X = SCREEN_WIDTH - 50;
    int BOX_HEIGHT = 50;
    int BOX_WIDTH = BOX_HEIGHT;
    int RELATIVE_Y0 = SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT + ((BOTTOM_BAR_HEIGHT-BOX_HEIGHT)/2) + 10;
    rectangleRGBA(renderer, END_X - 3*BOX_WIDTH, RELATIVE_Y0, END_X - 2*BOX_WIDTH, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);
    rectangleRGBA(renderer, END_X - 2*BOX_WIDTH, RELATIVE_Y0, END_X - BOX_WIDTH, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);
    rectangleRGBA(renderer, END_X - BOX_WIDTH, RELATIVE_Y0, END_X, RELATIVE_Y0 + BOX_HEIGHT, 255, 255, 255, 255);

    // write header text
    drawText("KEY RESOURCES", END_X - 150, RELATIVE_Y0 - 25, 255, 255, 255);

    // create background texture (plain wall / dark grey)
    SDL_Surface* image = IMG_Load("../resource/plain_wall.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, image);
    if (background == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;

    // draw resources if owned by player
    if (player.getKeyResource(0) == 1) {
        SDL_Surface* image = IMG_Load("../resource/key_power.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key1 = SDL_CreateTextureFromSurface(renderer, image);
        if (key1 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key1_rect = { END_X - 3*BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, background, NULL, &key1_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, key1, NULL, &key1_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key1);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
    if (player.getKeyResource(1) == 1) {
        SDL_Surface* image = IMG_Load("../resource/key_wire.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key2 = SDL_CreateTextureFromSurface(renderer, image);
        if (key2 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key2_rect = { END_X - 2*BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, background, NULL, &key2_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, key2, NULL, &key2_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key2);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
    if (player.getKeyResource(2) == 1) {
        SDL_Surface* image = IMG_Load("../resource/key_nuclear.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* key3 = SDL_CreateTextureFromSurface(renderer, image);
        if (key3 == NULL) csci437_error("Could not create texture from surface!");
        SDL_Rect key3_rect = { END_X - BOX_WIDTH, RELATIVE_Y0, BOX_WIDTH, BOX_HEIGHT };
        SDL_RenderCopyEx(renderer, background, NULL, &key3_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, key3, NULL, &key3_rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(key3);
        // free surface
        SDL_FreeSurface( image );
        image = NULL;
    }
    // destroy background texture
    SDL_DestroyTexture(background);
}


// draw battle UI
void Renderer::drawBattleUI(const Player &player) {
    // figure out which moves are possible
    std::array<bool, 12> moves = player.getPossibleBattleMoves();
    
    // adjustable parameters for what the UI looks like
    int RELATIVE_X0 = 100;
    int RELATIVE_Y0 = 100;
    int ACTION_BOX_WIDTH = 250;
    int ACTION_BOX_HEIGHT = 30;
    int LEFT_BORDER = 25;
    int VERTICAL_SPACING = 10;
    int PREV_BOX_HEIGHT = ACTION_BOX_HEIGHT + VERTICAL_SPACING;
    int BACKGROUND_WIDTH = 3*LEFT_BORDER + 2*ACTION_BOX_WIDTH;
    int BACKGROUND_HEIGHT = VERTICAL_SPACING + 6*PREV_BOX_HEIGHT;

    // background rectangle
    boxRGBA(renderer, RELATIVE_X0, RELATIVE_Y0, RELATIVE_X0 + BACKGROUND_WIDTH, RELATIVE_Y0 + BACKGROUND_HEIGHT, 56, 0, 59, 255);
    // action backgrounds
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);
    boxRGBA(renderer, RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT, RELATIVE_X0 + 2*LEFT_BORDER + 2*ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 203, 179, 204, 255);

    // if the player can do the move, write the text in black. otherwise, write the text in grey.
    if (moves[0]) {
        drawText("0", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("0", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
        drawText("Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
    }
    
    if (moves[1]) {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Bandage Wounds", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Bandage Wounds", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[2]) {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[3]) {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Block Attack", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Block Attack", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[4]) {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[5]) {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Electric Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[6]) {
        drawText("6", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Time Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("6", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
        drawText("Time Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[7]) {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[8]) {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Make a Tourniquet", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Make a Tourniquet", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[9]) {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[10]) {
        drawText("-", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("-", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[11]) {
        drawText("=", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("=", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

}

// draw scene background
void Renderer::drawScene(const Scene &scene) {
    // get the info of the scene layout
    int** layout = scene.getSceneLayout();
    const int numRows = scene.getSceneRows();
    const int numColumns = scene.getSceneColumns();

    // calculate how wide/tall each scene tile should be
    const int screenBlockWidth = SCREEN_WIDTH/numColumns;
    const int screenBlockHeight = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/numRows;

    // make resources slightly smaller than the tile they are in
    const int RESOURCE_HEIGHT = screenBlockHeight - 5;
    const int RESOURCE_WIDTH = RESOURCE_HEIGHT;

    // based on the resource size relative to the tile size, set where the upper left corner of the resource image should be
    const int LEFT_BORDER = (screenBlockWidth - RESOURCE_WIDTH)/2;
    const int VERTICAL_BORDER = (screenBlockHeight - RESOURCE_HEIGHT)/2;

    // create textures
    // scrap metal
    SDL_Surface* image = IMG_Load("../resource/metal.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scrap_metal = SDL_CreateTextureFromSurface(renderer, image);
    if (scrap_metal == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // rags
    image = IMG_Load("../resource/rags.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* rags = SDL_CreateTextureFromSurface(renderer, image);
    if (rags == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // oil
    image = IMG_Load("../resource/oil.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* oil = SDL_CreateTextureFromSurface(renderer, image);
    if (oil == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // power source
    image = IMG_Load("../resource/power.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* power = SDL_CreateTextureFromSurface(renderer, image);
    if (power == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // wires
    image = IMG_Load("../resource/wire.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* wire = SDL_CreateTextureFromSurface(renderer, image);
    if (wire == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // nuclear waste
    image = IMG_Load("../resource/nuclear.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* nuclear = SDL_CreateTextureFromSurface(renderer, image);
    if (nuclear == NULL) csci437_error("Could not create texture from surface!");
    // free surface
    SDL_FreeSurface( image );
    image = NULL;
    // rocks
    image = IMG_Load("../resource/Wall.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* rock = SDL_CreateTextureFromSurface(renderer, image);
    if (rock == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // ground backgrounds
    image = IMG_Load("../resource/scene_background.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scene_background = SDL_CreateTextureFromSurface(renderer, image);
    if (scene_background == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    image = IMG_Load("../resource/scene_background_2.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scene_background_2 = SDL_CreateTextureFromSurface(renderer, image);
    if (scene_background_2 == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    image = IMG_Load("../resource/scene_background_3.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* scene_background_3 = SDL_CreateTextureFromSurface(renderer, image);
    if (scene_background_3 == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // left facing wall
    // right facing wall
    // up facing wall
    // down facing wall
    image = IMG_Load("../resource/Gray_Building_Side.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* wall = SDL_CreateTextureFromSurface(renderer, image);
    if (wall == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // two sided vertical wall
    // two sided horizontal wall
    image = IMG_Load("../resource/double_sided_wall.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* dsw = SDL_CreateTextureFromSurface(renderer, image);
    if (dsw == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;    
    // plain grey wall
    image = IMG_Load("../resource/plain_wall.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* plain_wall = SDL_CreateTextureFromSurface(renderer, image);
    if (plain_wall == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;       
    // inner corner top right
    // inner corner top left
    // inner corner bottom left
    // inner corner bottom right
    image = IMG_Load("../resource/Gray_Building_Inner_Corner.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* inner_corner = SDL_CreateTextureFromSurface(renderer, image);
    if (inner_corner == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;      
    // outer corner top right
    // outer corner top left
    // outer corner bottom left
    // outer corner bottom right
    image = IMG_Load("../resource/Gray_Building_Outer_Corner.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* outer_corner = SDL_CreateTextureFromSurface(renderer, image);
    if (outer_corner == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    // inner corner double bottom
    // inner corner double top
    // inner corner double left
    // inner corner double right
    image = IMG_Load("../resource/inner_corner_double.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* double_inner_corner = SDL_CreateTextureFromSurface(renderer, image);
    if (double_inner_corner == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    // crowbar
    image = IMG_Load("../resource/crowbar.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* crowbar = SDL_CreateTextureFromSurface(renderer, image);
    if (crowbar == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    // key resources
    image = IMG_Load("../resource/key_power.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* key_power = SDL_CreateTextureFromSurface(renderer, image);
    if (key_power == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    image = IMG_Load("../resource/key_wire.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* key_wire = SDL_CreateTextureFromSurface(renderer, image);
    if (key_wire == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    image = IMG_Load("../resource/key_nuclear.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* key_nuclear = SDL_CreateTextureFromSurface(renderer, image);
    if (key_nuclear == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 
    // lab tiles
    image = IMG_Load("../resource/Lab_Inner_Corner.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* lab_inner_corner = SDL_CreateTextureFromSurface(renderer, image);
    if (lab_inner_corner == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = IMG_Load("../resource/Lab_Inner_No_Lights.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* lab_pw = SDL_CreateTextureFromSurface(renderer, image);
    if (lab_pw == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = IMG_Load("../resource/Lab_Inner.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* lab_lights = SDL_CreateTextureFromSurface(renderer, image);
    if (lab_lights == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = IMG_Load("../resource/Lab_Outer_Corner.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* lab_outer_corner = SDL_CreateTextureFromSurface(renderer, image);
    if (lab_outer_corner == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = IMG_Load("../resource/Lab_Side.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* lab_side = SDL_CreateTextureFromSurface(renderer, image);
    if (lab_side == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL; 

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++) {
            if (layout[i][j] == METAL) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect scrap_metal_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, scrap_metal, NULL, &scrap_metal_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == RAGS) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect rags_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, rags, NULL, &rags_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == OIL) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect oil_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, oil, NULL, &oil_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == POWER) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect power_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, power, NULL, &power_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == WIRE) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect wire_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, wire, NULL, &wire_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == NUCLEAR) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect nuclear_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, nuclear, NULL, &nuclear_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ROCK) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect rock_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, rock, NULL, &rock_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LFW) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == RFW) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == UFW) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == DFW) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == TSVW) {
                SDL_Rect dsw_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, dsw, NULL, &dsw_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == TSHW) {
                SDL_Rect dsw_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, dsw, NULL, &dsw_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == PW) {
                SDL_Rect plain_wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, plain_wall, NULL, &plain_wall_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICTR) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICTL) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICBL) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 90, NULL, SDL_FLIP_VERTICAL);
            } else if (layout[i][j] == ICBR) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == OCTR) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == OCTL) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 180, NULL, SDL_FLIP_VERTICAL);
            } else if (layout[i][j] == OCBL) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == OCBR) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICDB) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICDT) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICDL) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == ICDR) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 90, NULL, SDL_FLIP_VERTICAL);
            } else if (layout[i][j] == CROWBAR) {
                SDL_Rect crowbar_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &crowbar_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, crowbar, NULL, &crowbar_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == KEY_POWER) {
                SDL_Rect key_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, key_power, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == KEY_WIRE) {
                SDL_Rect key_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, key_wire, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == KEY_NUCLEAR) {
                SDL_Rect key_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background_2, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, key_nuclear, NULL, &key_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_LFW) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_side, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_RFW) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_side, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            } else if (layout[i][j] == LAB_UFW) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_side, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_DFW) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_side, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_PW) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_pw, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_ICTR) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_inner_corner, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            } else if (layout[i][j] == LAB_ICTL) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_inner_corner, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_ICBR) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_inner_corner, NULL, &rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_ICBL) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_inner_corner, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_OCTR) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_outer_corner, NULL, &rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_OCTL) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_outer_corner, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_OCBL) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_outer_corner, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_OCBR) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_outer_corner, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == LAB_LIGHTS) {
                SDL_Rect rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, lab_lights, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            } else { // just ground -- use one of the three ground backgrounds and rotate to create variety
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight};
                if (i%3 == 0 && i%2 == 0 && j%2 == 0 && j%7 == 0 && scene.getSceneID()%2 == 0 && scene.getsceneCategoryID()%2 == 0) {
                    SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
                else if (i%2 == 0 && j%3 == 0) {
                    SDL_RenderCopyEx(renderer, scene_background_3, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
                else if (i%4 == 0 && scene.getSceneID()%2 == 1) {
                    SDL_RenderCopyEx(renderer, scene_background_3, NULL, &scene_rect, 0, NULL, SDL_FLIP_VERTICAL);   
                }
                else if (j%5 == 0) {
                    SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_HORIZONTAL);   
                }
                else {
                    SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
            }
        }
    }

    // destroy all textures
    SDL_DestroyTexture(scrap_metal);
    SDL_DestroyTexture(rags);
    SDL_DestroyTexture(oil);
    SDL_DestroyTexture(power);
    SDL_DestroyTexture(wire);
    SDL_DestroyTexture(nuclear);
    SDL_DestroyTexture(rock);
    SDL_DestroyTexture(scene_background);
    SDL_DestroyTexture(scene_background_2);
    SDL_DestroyTexture(scene_background_3);
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(dsw);
    SDL_DestroyTexture(plain_wall);
    SDL_DestroyTexture(inner_corner);
    SDL_DestroyTexture(outer_corner);
    SDL_DestroyTexture(double_inner_corner);
    SDL_DestroyTexture(crowbar);
    SDL_DestroyTexture(key_power);
    SDL_DestroyTexture(key_wire);
    SDL_DestroyTexture(key_nuclear);
    SDL_DestroyTexture(lab_inner_corner);
    SDL_DestroyTexture(lab_pw);
    SDL_DestroyTexture(lab_lights);
    SDL_DestroyTexture(lab_outer_corner);
    SDL_DestroyTexture(lab_side);
}

// draw the bottom bar space and its contents
void Renderer::drawBottomBar(const Player &player) {
    // Draw line for bottom bar
    thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
    // Update health bar
    drawHealthBar(player);
    drawInventory(player);
    drawKeyInventory(player);
}

// draw the help screen
void Renderer::drawHelpScreen() {
    SDL_Surface* image = IMG_Load("../resource/help_screen.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* help_screen = SDL_CreateTextureFromSurface(renderer, image);
    if (help_screen == NULL) csci437_error("Could not create texture from surface!");
    SDL_FreeSurface( image );
    image = NULL;
    // HELP_SCREEN_WIDTH and HELP_SCREEN_HEIGHT are constants from the constants.h file
    SDL_Rect help_screen_rect = { (SCREEN_WIDTH-HELP_SCREEN_WIDTH)/2, (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT-HELP_SCREEN_HEIGHT)/2, HELP_SCREEN_WIDTH, HELP_SCREEN_HEIGHT };
    SDL_RenderCopyEx(renderer, help_screen, NULL, &help_screen_rect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(help_screen);
}

void Renderer::drawHelpMessage() {
    boxRGBA(renderer, SCREEN_WIDTH - 155, 30, SCREEN_WIDTH, 0, 100, 100, 100, 255);
    drawText("Press h for help", SCREEN_WIDTH - 140, 4, 255, 255, 255);
}

// draw the basic aspects of each scene
void Renderer::window_update(const Player &player, const bool &world, Scene &scene) {
    // if not in battle, need bottom bar, scene background, and player
    if (world) {
        drawBottomBar(player);
        drawScene(scene);
        drawHelpMessage();
        drawPlayer(player, world);
    }
    else { // in battle; need background, bottom bar, battle UI, and player
        // draw background
        SDL_Surface* image = IMG_Load("../resource/Background_Grass.png");
        if (image == NULL) csci437_img_error("Could not create image!");
        SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, image);
        if (background == NULL) csci437_error("Could not create texture from surface!");
        SDL_FreeSurface( image );
        image = NULL;
        SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT };
        SDL_RenderCopyEx(renderer, background, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(background);
        // draw other elements
        drawBottomBar(player);
        drawBattleUI(player);
        drawPlayer(player, world);
        drawHelpMessage();
    }
}

// present the renderer
void Renderer::renderer_present() {
    SDL_RenderPresent(renderer);
}



