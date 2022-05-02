#ifndef BIONIC_APOCALYPSE_SAVESYSTEM_H
#define BIONIC_APOCALYPSE_SAVESYSTEM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

void save_gameState(int health);

void read_gameState();

#endif
