#include "Enemy.h"
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = xp;
}

void Enemy::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Enemy::getPosition(int & x, int & y)
{
	x = _x;
	y = _y;
}

int Enemy::attack()
{
	static default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

// Returns 0 if enemy survives; returns xp value if enemy dies
int Enemy::takeDamage(int attack)
{
	attack -= _defense;
	// Check if attack does damage
	if (attack > 0) {
		_health -= attack;
		// Check if dead
		if (_health <= 0)
			return _experienceValue;
	}
	
	return 0;
}

char Enemy::getMove(int playerX, int playerY)
{
	static default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> moveRoll(0, 6);

	// Distance from the enemy to the player
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);
	int distance = adx + ady;

	if (distance < 5) {
		// Moving along X axis
		if (adx > ady) {
			if (dx > 0)
				return 'a';
			else
				return 'd';
		}
		// Moving along the Y axis
		else {
			if (dy > 0)
				return 'w';
			else
				return 's';
		}
	}

	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}
}