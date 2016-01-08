#pragma once
#include <string>

class Enemy
{
public:
	Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp);

	void setPosition(int x, int y);
	void getPosition(int& x, int& y);

	std::string getName() { return _name; }
	char getTile() { return _tile; }

	int attack();
	int takeDamage(int attack);

	char getMove(int playerX, int playerY);

private:
	std::string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;

	int _x;
	int _y;
};

