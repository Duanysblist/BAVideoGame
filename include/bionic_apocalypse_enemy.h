#include "bionic_apocalypse_renderer.h"
#include "bionic_apocalypse_player.h"

#ifndef BIONIC_APOCALYPSE_ENEMY_H
#define BIONIC_APOCALYPSE_ENEMY_H

class Enemy {

public: 
	int getHealth() const;
	void setHealth(int newHealth);
	//Adds or Subtracts from the health of the enemy
	void changeHealth(int healthChange);
	//Chooses a random attack from the enemy's arsenal
	int randomAttack() const;
	void setPosX(int newX);
	void setPosY(int newY);
	int getX() const;
	int getY() const;
	void setStartLocation(int X, int Y);
	void setEndLocation(int X, int Y);
	bool playerCollisionCheck(Player player) const;
	void update(Renderer* renderer);
	// void draw(Renderer renderer);
};

#endif