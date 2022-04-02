#include <string>
#include "bionic_apocalypse_enemy.h"
#include "bionic_apocalypse_constants.h"

#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

class Renderer {
    public:
        void csci437_error(const std::string& msg);

        void csci437_img_error(const std::string& msg);

        void csci437_ttf_error(const std::string& msg);

        void drawHealthBar();

        void drawBattleUI();

        void drawText(const char* words, int dst_x, int dst_y, int r, int g, int b);

        void drawInventory();

        void drawKeyInventory();

        void window_startup();

        void window_clear();

        void window_update(const bool world);

        void drawPlayer(const bool world);

        void drawEnemy(Enemy foe);

        void drawBattleUI(const char* action1, const char* action2, const char* action3, const char* action4);
};

#endif
