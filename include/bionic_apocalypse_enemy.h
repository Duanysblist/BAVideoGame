
#ifndef BIONIC_APOCALYPSE_ENEMY_H
#define BIONIC_APOCALYPSE_ENEMY_H

#include "bionic_apocalypse_player.h"
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
		int maxHealth = 100;
		int enemyAttacks[3] = { -5, -10, -15};
		int enemyPosX;
		int enemyPosY;
		int startLocation [2] = {500,500};
		int endLocation [2] = {900,250};
		bool goingToStart = false;
		int enemyType = 0; //0 is normal, -1, is tank, and 1 is glass cannon

		int id;

	public: 
		Enemy(){
			alive = true;
			enemyHealth = 100;
			maxHealth = 100;
			goingToStart = false;
			enemyType = -2;
			enemyPosX = 500;
			enemyPosY = 500;
			id = -1;
		}
		int getHealth() const;
		void setHealth(const int newHealth);
		//Adds or Subtracts from the health of the enemy
		void changeHealth(const int healthChange);
		
		//Chooses a random attack from the enemy's arsenal
		int randomAttack() const;

		// position methods
		void setPosX(const int newX);
		void setPosY(const int newY);
		int getX() const;
		int getY() const;

		void setStartLocation(const int X, const int Y);
		void setEndLocation(const int X, const int Y);

		// updates enemy location
		void update(const int dt);

		int getType();
		void setType(const int type);

		void setAlive(const bool stat);
		bool getAlive() const;

		int getMaxHealth() const;

		int getID();
		void setID(const int id);
};

#endif