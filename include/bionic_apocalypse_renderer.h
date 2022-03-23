#include <string>
#include "bionic_apocalypse_enemy.h"

#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

void csci437_error(const std::string& msg);

void csci437_img_error(const std::string& msg);

void csci437_ttf_error(const std::string& msg);

void window_startup();

void window_clear();

void window_update();

void drawPlayer();

void drawEnemy(Enemy* foe);

#endif
