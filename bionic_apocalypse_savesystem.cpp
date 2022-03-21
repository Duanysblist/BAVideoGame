#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

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