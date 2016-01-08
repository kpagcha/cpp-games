#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

class Level
{
public:
	Level();

	void load(std::string fileName, Player& player);
	void print();

	void movePlayer(char input, Player& player);
	void updateEnemies(Player& player);

	char getTile(int x, int y);
	void setTile(int x, int y, char tile);

private:
	void processPlayerMove(Player& player, int targetX, int targetY);
	void processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY);
	void battleEnemy(Player& player, int targetX, int targetY);

	std::vector<std::string> _levelData;
	std::vector<Enemy> _enemies;
};

