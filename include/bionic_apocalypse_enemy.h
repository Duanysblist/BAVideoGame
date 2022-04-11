
#ifndef BIONIC_APOCALYPSE_ENEMY_H
#define BIONIC_APOCALYPSE_ENEMY_H

#include "bionic_apocalypse_player.h"
#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

class Enemy {

	private:
		bool alive = true;
		int enemyHealth = 100;
		int enemyAttacks [3] = { -4,-8,-12 };
		int enemyPosX;
		int enemyPosY;
		int startLocation [2] = {500,500};
		int endLocation [2] = {900,250};
		bool goingToStart = false;

	public: 
		int getHealth() const;
		void setHealth(const int newHealth);
		//Adds or Subtracts from the health of the enemy
		void changeHealth(const int healthChange);
		//Chooses a random attack from the enemy's arsenal
		int randomAttack() const;
		void setPosX(const int newX);
		void setPosY(const int newY);
		int getX() const;
		int getY() const;
		void setStartLocation(const int X, const int Y);
		void setEndLocation(const int X, const int Y);
		bool playerCollisionCheck(const Player player) const;
		void update(Renderer* renderer);
		// void draw(Renderer renderer);
};

#endif