#include "Level.h"
#include <fstream>
#include <iostream>

using namespace std;

Level::Level()
{
}

void Level::load(std::string fileName, Player& player)
{
	// Loads the level

	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;
	while (getline(file, line))
		_levelData.push_back(line);

	// Process the level

	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			case 'S':
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
				break;
			case 'O':
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 40, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}

void Level::print()
{
	cout << string(100, '\n');
	for (int i = 0; i < _levelData.size(); i++)
		printf("%s\n", _levelData[i].c_str());
	printf("\n");
}

void Level::movePlayer(char input, Player& player)
{
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	switch (input) {
	case 'w':
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid input!\n");
		system("PAUSE");
	}
}

void Level::updateEnemies(Player& player)
{
	char aiMove;
	int playerX, playerY, enemyX, enemyY;
	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) {
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player & player, int targetX, int targetY)
{
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleEnemy(player, targetX, targetY);
		break;
	}
}

void Level::processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY)
{
	int playerX, playerY, enemyX, enemyY;

	player.getPosition(playerX, playerY);
	_enemies[enemyIndex].getPosition(enemyX, enemyY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::battleEnemy(Player& player, int targetX, int targetY)
{
	int enemyX, enemyY, attackRoll, attackResult;

	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(enemyX, enemyY);

		if (targetX == enemyX && targetY == enemyY) {
			// Battle enemy
			attackRoll = player.attack();
			attackResult = _enemies[i].takeDamage(attackRoll);

			//printf("Player attacked %s with a roll of %d. ", _enemies[i].getName().c_str(), attackRoll);
			cout << "\nPlayer attacked " << _enemies[i].getName() << " with a roll of " << attackRoll << endl;

			// Enemy dies
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');

				//printf("%s died!\n", _enemies[i].getName().c_str());
				print();
				cout << "Player attacked " << _enemies[i].getName() << " with a roll of " << attackRoll << endl;
				cout << _enemies[i].getName() << " died!" << endl;

				_enemies[i] = _enemies.back();
				_enemies.pop_back();

				system("PAUSE");

				player.addExperience(attackResult);

				return;
			}
			// Enemy fights back
			attackRoll = _enemies[i].attack();
			attackResult = player.takeDamage(attackRoll);

			cout << _enemies[i].getName() << " attacked player with a roll of " << attackRoll << endl;

			// Player dies
			if (attackResult) {
				int playerX, playerY;
				player.getPosition(playerX, playerY);

				setTile(playerX, playerY, 'x');
				
				print();
				printf("YOU DIED!\n");

				system("PAUSE");

				exit(0);
			}
			
			system("PAUSE");

			return;
		}
	}
}

