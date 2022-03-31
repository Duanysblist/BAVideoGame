#include <string>
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_constants.h"

#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

void csci437_error(const std::string& msg);

void csci437_img_error(const std::string& msg);

void csci437_ttf_error(const std::string& msg);

void drawHealthBar();

void window_startup();

void window_clear();

void window_update(const bool world);

void drawPlayer(const bool world);

void drawEnemy(Enemy* foe);



#endif
