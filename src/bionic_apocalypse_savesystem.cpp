
#include "bionic_apocalypse_savesystem.h"



void save_gameState(int health) {
	ofstream outStream;
	outStream.open("save_file.txt");
	if (outStream.fail()) {
		std::cout << "File opening failed. \n";
		exit(1);
	}

	std::cout << health;

	outStream << health << endl;
	outStream.close();
}

void read_gameState() {
	ifstream inStream;
	inStream.open("save_file.txt");
	if (inStream.fail()) {
		std::cout << "File opening failed. \n";
		exit(1);
	}

	int health;
	inStream >> health;
	inStream.close();

	std::cout << health;
}