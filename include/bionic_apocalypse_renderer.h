#include <string>

#ifndef BIONIC_APOCALYPSE_RENDERER_H
#define BIONIC_APOCALYPSE_RENDERER_H

void csci437_error(const std::string& msg);

void csci437_img_error(const std::string& msg);

void csci437_ttf_error(const std::string& msg);

void window_startup();

void window_update();

#endif
