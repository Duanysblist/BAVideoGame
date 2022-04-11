#include "bionic_apocalypse_renderer.h"

void Renderer::csci437_error(const std::string& msg) const
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void Renderer::csci437_img_error(const std::string& msg) const
{
    std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
    exit(0);
}

void Renderer::csci437_ttf_error(const std::string& msg) const
{
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

void Renderer::drawPlayer(const Player player, const bool world) {
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

void Renderer::drawEnemy(const int posX, const int posY) {
    image = IMG_Load("../resource/enemy_texture.png");
    if (image == NULL) csci437_img_error("Could not create image!");
    SDL_Texture* enemy_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (enemy_texture == NULL) csci437_error("Could not create texture from surface!");

    enemy_rect = { posX, posY, ENEMY_WIDTH, ENEMY_HEIGHT };
    SDL_RenderCopyEx(renderer, enemy_texture, NULL, &enemy_rect, 0, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(enemy_texture);
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

void Renderer::drawHealthBar(const Player player) {
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

void Renderer::drawInventory(const Player player) {
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
    //SDL_Destroy 
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

void Renderer::drawKeyInventory(const Player player) {
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

void Renderer::drawBattleUI(const char* action1, const char* action2, const char* action3, const char* action4) {
    int RELATIVE_X0 = 100;
    int RELATIVE_Y0 = 100;
    int ACTION_BOX_WIDTH = 250;
    int ACTION_BOX_HEIGHT = 30;
    int LEFT_BORDER = 25;
    int VERTICAL_SPACING = 20;
    int PREV_BOX_HEIGHT = ACTION_BOX_HEIGHT + VERTICAL_SPACING;
    int BACKGROUND_WIDTH = 2*LEFT_BORDER + ACTION_BOX_WIDTH;
    int BACKGROUND_HEIGHT = VERTICAL_SPACING + 4*PREV_BOX_HEIGHT;

    // CURRENT COLORS ARE JUST PLACEHOLDERS -- CAN BE CHANGED
    // background rectangle
    boxRGBA(renderer, RELATIVE_X0, RELATIVE_Y0, RELATIVE_X0 + BACKGROUND_WIDTH, RELATIVE_Y0 + BACKGROUND_HEIGHT, 255, 210, 210, 255);
    // action backgrounds
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    boxRGBA(renderer, RELATIVE_X0 + LEFT_BORDER, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT, RELATIVE_X0 + LEFT_BORDER + ACTION_BOX_WIDTH, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + ACTION_BOX_HEIGHT, 255, 240, 240, 255);
    // action labels
    drawText("1", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText("2", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + PREV_BOX_HEIGHT + 5, 0, 0, 0);
    drawText("3", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 2*PREV_BOX_HEIGHT + 5, 0, 0, 0);
    drawText("4", RELATIVE_X0 + LEFT_BORDER + 10, RELATIVE_Y0 + VERTICAL_SPACING + 3*PREV_BOX_HEIGHT + 5, 0, 0, 0);
    // action text
    drawText(action1, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action2, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action3, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 2*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
    drawText(action4, RELATIVE_X0 + LEFT_BORDER + 30, RELATIVE_Y0 + 3*PREV_BOX_HEIGHT + VERTICAL_SPACING + 5, 0, 0, 0);
}

void Renderer::window_update(const Player player, const bool world) {
    if (world) {
        // Draw line for bottom bar
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar(player);
        drawInventory(player);
        drawKeyInventory(player);
        // Used to show the two dimensional array indexes on the screen
        // @TODO: Need to change this to create a different background
        std::vector<int> a = player.getPlayerMapPosition();
        int int_positionx = a.at(0);
        int int_positiony = a.at(1);
        std::string positionx = std::to_string(int_positionx);
        std::string positiony = std::to_string(int_positiony);
        std::string position = positionx + positiony;
        char const *p_char = position.c_str();
        drawText(p_char, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255);

        SDL_RenderPresent(renderer);
    }
    else {
        thickLineRGBA(renderer, 0, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BOTTOM_BAR_HEIGHT, 4, 255, 255, 255, 255);
        // Update health bar
        drawHealthBar(player);
        drawInventory(player);
        drawKeyInventory(player);
        /** draw battle UI -- currently commented out since this is likely not where it would be called
        // you can un-comment it just to see what it will look like (it shows up in battle mode when called here)
        drawBattleUI("Action one", "Action two", "Action three", "Action four");
        **/
        SDL_RenderPresent(renderer);
    }
}



