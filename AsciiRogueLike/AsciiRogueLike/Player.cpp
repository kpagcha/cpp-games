#include "Player.h"
#include <random>
#include <ctime>

using namespace std;

Player::Player()
{
	_x = 0;
	_y = 0;
}

void Player::init(int level, int health, int attack, int defense, int experience)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::getPosition(int & x, int & y)
{
	x = _x;
	y = _y;
}

int Player::attack()
{
	static default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

// Returns true if player dies; returns false if player survives
bool Player::takeDamage(int attack)
{
	attack -= _defense;
	// Check if attack does damage
	if (attack > 0) {
		_health -= attack;
		// Check if dead
		if (_health <= 0)
			return true;
	}

	return false;
}


void Player::addExperience(int xp)
{
	_experience += xp;

	// Level up
	while (_experience > 50) {
		printf("Leveled up!\n");

		_level++;
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health += 10;

		system("PAUSE");
	}
}

