#include "bionic_apocalypse_battlelogic.h"

void Battle::startNewBattle(Enemy &enemy) {
	// std::cout << "battle and bad guy initiated" << std::endl; 
	myEnemy = enemy;
	active = true;
}

void Battle::setAttackingTrue(Player &player, int move) {
	if (player.getPlayerHealth() > 0 && myEnemy.getHealth() > 0) {
		std::array<bool, 12> moves = player.getPossibleBattleMoves();
		if (moves[move]) {
			
		}
		myEnemy.changeHealth(-9);
		player.changePlayerHealth(myEnemy.randomAttack());
		//std::cout << "Player HP: " << player.getPlayerHealth() << ", Enemy HP: " << mainEnemy.getHealth() << std::endl;
		// std::cout << "Attacking" << "\n";
	}
	else {
		active = false;
	}
}

bool Battle::getStatus() {
	return active;
}