#pragma once
#include <vector>
#include <string>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

//The level stores the data for the level and the enemy list, and does a lot
//of the core game logic
class Level
{
public:
	Level();

	void load(string fileName, Player &player);
	void print();

	void movePlayer(char input, Player &player);
	void updateEnemies(Player &player);

	//Getters
	char getTile(int x, int y);
	//Setters
	void setTile(int x, int y, char tile);
	void setNumPrints(int numPrints) { _numPrints = _numPrints; }

private:
	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);

private:
	// I added this variable to keep track of how many lines we printed, so that we can pad
	// the bottom of the screen with newlines to keep the game board from jumping around!
	int _numPrints;
	// Stores the level information
	vector <string> _levelData;
	vector <Enemy> _enemies;
};

