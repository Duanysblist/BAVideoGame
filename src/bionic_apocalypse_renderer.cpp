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
        player_rect = { player.getPlayerScreenPositionX(), player.getPlayerScreenPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT };
        SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, 0, NULL, SDL_FLIP_NONE);
    }
    else {
        player_rect = {0, SCREEN_HEIGHT - (BOTTOM_BAR_HEIGHT+PLAYER_HEIGHT), PLAYER_WIDTH, PLAYER_HEIGHT};
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
    SDL_FreeSurface(image);
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
    // write quantity
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
    int END_X = SCREEN_WIDTH - 50;
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

    
    if (moves[0]) {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
        drawText("Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
    }
    
    if (moves[1]) {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Bandage Wounds", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Bandage Wounds", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[2]) {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Throwing Knives", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[3]) {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Block Attack", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Block Attack", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[4]) {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("5", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 4*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Molotov", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 4*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[5]) {
        drawText("6", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("6", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5*PREV_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Electric Crowbar Strike", RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 5*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[6]) {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
        drawText("Time Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    }
    else {
        drawText("7", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
        drawText("Time Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 153, 143, 153);
    }

    if (moves[7]) {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("8", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Electric Net", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 2*VERTICAL_SPACING + ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[8]) {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Trip Enemy", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("9", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Trip Enemy", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 30, RELATIVE_Y0 + 3*VERTICAL_SPACING + 2*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[9]) {
        drawText("10", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("10", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Small Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 4*VERTICAL_SPACING + 3*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[10]) {
        drawText("11", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("11", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Large Nuclear Bomb", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 5*VERTICAL_SPACING + 4*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

    if (moves[11]) {
        drawText("12", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 0, 0, 0);
    }
    else {
        drawText("12", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 10, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
        drawText("Nuclear Projectile", RELATIVE_X0 + 2*LEFT_BORDER + ACTION_BOX_WIDTH + 40, RELATIVE_Y0 + 6*VERTICAL_SPACING + 5*ACTION_BOX_HEIGHT + 5, 153, 143, 153);
    }

}

void Renderer::drawScene(const Scene &scene) {
    int** layout = scene.getSceneLayout();
    const int numRows = scene.getSceneRows();
    const int numColumns = scene.getSceneColumns();

    const int screenBlockWidth = SCREEN_WIDTH/numColumns;
    const int screenBlockHeight = (SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT)/numRows;

    const int RESOURCE_HEIGHT = screenBlockHeight - 5;
    const int RESOURCE_WIDTH = RESOURCE_HEIGHT;

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
    // scene backgrounds
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

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numColumns; j++) {
        // 2 - space in scene has scrap metal
        // 3 - space in scene has rags
        // 4 - space in scene has oil
        // 5 - space in scene has power source
        // 6 - space in scene has wire
        // 7 - space in scene has nuclear waste
            if (layout[i][j] == 2) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect scrap_metal_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, scrap_metal, NULL, &scrap_metal_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 3) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect rags_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, rags, NULL, &rags_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 4) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect oil_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, oil, NULL, &oil_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 5) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect power_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, power, NULL, &power_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 6) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect wire_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, wire, NULL, &wire_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 7) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect nuclear_rect = { j*screenBlockWidth + LEFT_BORDER, i*screenBlockHeight + VERTICAL_BORDER, RESOURCE_WIDTH, RESOURCE_HEIGHT };
                SDL_RenderCopyEx(renderer, nuclear, NULL, &nuclear_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 1) {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_Rect rock_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, rock, NULL, &rock_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 11) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 12) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 13) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 14) {
                SDL_Rect wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, wall, NULL, &wall_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 15) {
                SDL_Rect dsw_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, dsw, NULL, &dsw_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 16) {
                SDL_Rect dsw_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, dsw, NULL, &dsw_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 17) {
                SDL_Rect plain_wall_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, plain_wall, NULL, &plain_wall_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 18) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 19) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 270, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 20) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 90, NULL, SDL_FLIP_VERTICAL);
            } else if (layout[i][j] == 21) {
                SDL_Rect inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, inner_corner, NULL, &inner_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 22) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 23) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 180, NULL, SDL_FLIP_VERTICAL);
            } else if (layout[i][j] == 24) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 25) {
                SDL_Rect outer_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, scene_background, NULL, &outer_corner_rect, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, outer_corner, NULL, &outer_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 26) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 0, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 27) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 180, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 28) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 90, NULL, SDL_FLIP_NONE);
            } else if (layout[i][j] == 28) {
                SDL_Rect double_inner_corner_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight };
                SDL_RenderCopyEx(renderer, double_inner_corner, NULL, &double_inner_corner_rect, 90, NULL, SDL_FLIP_VERTICAL);
            } else {
                SDL_Rect scene_rect = { j*screenBlockWidth, i*screenBlockHeight, screenBlockWidth, screenBlockHeight};
                if (i%3 == 0 && i%2 == 0 && j%2 == 0 && scene.getSceneID()%2 == 0) {
                    SDL_RenderCopyEx(renderer, scene_background, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
                else if (i%2 == 0 && j%3 == 0) {
                    SDL_RenderCopyEx(renderer, scene_background_2, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
                else {
                    SDL_RenderCopyEx(renderer, scene_background_3, NULL, &scene_rect, 0, NULL, SDL_FLIP_NONE);   
                }
            }
        }
    }

    // destroy textures
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
}

void Renderer::drawBottomBar(const Player &player) {
    // Draw line for bottom bar
    thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
    // Update health bar
    drawHealthBar(player);
    drawInventory(player);
    drawKeyInventory(player);
}

void Renderer::window_update(const Player &player, const bool &world, Scene &scene) {
    if (world) {
        drawBottomBar(player);
        drawScene(scene);
        drawPlayer(player, world);
    }
    else {
        drawBottomBar(player);
        drawBattleUI(player);
        drawPlayer(player, world);
    }
}

void Renderer::renderer_present() {
    SDL_RenderPresent(renderer);
}



