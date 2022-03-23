#ifndef BIONIC_APOCALYPSE_ENEMY_H
#define BIONIC_APOCALYPSE_ENEMY_H

class Enemy {

public: 
	int getHealth();
	void setHealth(int newHealth);
	//Adds or Subtracts from the health of the enemy
	void changeHealth(int healthChange);
	//Chooses a random attack from the enemy's arsenal
	int randomAttack();
	void setPosX(int newX);
	void setPosY(int newY);
	int getX();
	int getY();
	void draw();
};

#endif