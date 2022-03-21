//#include "bionic_apocalypse_renderer.h"
//using namespace std;
//#include "bionic_apocalypse_player.h"
//using namespace std;
#include "bionic_apocalypse_savesystem.h"
using namespace std;


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;



int main(int argc, char** argv) {

    //Initialize helpful variables to use
    bool MOVE_UP = false;
    bool MOVE_DOWN = false;
    bool MOVE_RIGHT = false;
    bool MOVE_LEFT = false;
    bool INTERACTING = false;

	bool running = false;
    SDL_Event e;

    save_gameState(5);

    read_gameState();

	while (running) {

        //Check for input
        while (SDL_PollEvent(&e) != 0)
        {
            // User presses a key
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_q) {
                    running = false;
                }
                if (e.key.keysym.sym == SDLK_w) {
                    MOVE_UP = true;
                }
                if (e.key.keysym.sym == SDLK_s) {
                    MOVE_DOWN = true;
                }
                if (e.key.keysym.sym == SDLK_d) {
                    MOVE_RIGHT = true;
                }
                if (e.key.keysym.sym == SDLK_a) {
                    MOVE_LEFT = true;
                }
                if (e.key.keysym.sym == SDLK_SPACE) {
                    INTERACTING = true;
                }
            }

            // User releases a key
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_w) {
                    MOVE_UP = false;
                }
                if (e.key.keysym.sym == SDLK_s) {
                    MOVE_DOWN = false;
                }
                if (e.key.keysym.sym == SDLK_d) {
                    MOVE_RIGHT = false;
                }
                if (e.key.keysym.sym == SDLK_a) {
                    MOVE_LEFT = false;
                }
            }
        }

	}

    return 0;
}


void save_gameState(int health) {
    ofstream outStream;
    outStream.open("save_file.txt");
    if (outStream.fail()) {
        cout << "File opening failed. \n";
        exit(1);
    }

    cout << health;

    outStream << health << endl;
    outStream.close();
}

void read_gameState() {
    ifstream inStream;
    inStream.open("save_file.txt");
    if (inStream.fail()) {
        cout << "File opening failed. \n";
        exit(1);
    }

    int health;
    inStream >> health;
    inStream.close();

    cout << health;
}