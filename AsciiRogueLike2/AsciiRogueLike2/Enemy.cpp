#include "Enemy.h"

#include <random>
#include <ctime>


//Constructor initializes he enemy
Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp) {
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = xp;
}

//Sets the position of the enemy
void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

//Gets the position of the enemy using reference variables
void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

//Gets a random attack roll from 0 to _attack
int Enemy::attack() {
	//We use a static random engine so it only initializes once
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);
	// Return the random roll
	return attackRoll(randomEngine);
}

//Makes the enemy take damage according to its defense. Returns 0 if he didnt die, and _experienceValue if he did
int Enemy::takeDamage(int attack) {
	attack -= _defense;
	//check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		//check if he died
		if (_health <= 0) {
			return _experienceValue;
		}

	}
	return 0;
}

//This does the enemy AI
char Enemy::getMove(int playerX, int playerY) {

	int distance;
	//We get the distance from the player
	//so we know if we should move towards him
	//or just amble around randomly
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	distance = adx + ady;

	//If the distance is closer than 6 tiles, then we move towards the  player
	if (distance <= 5) {
		//Moving along X axis
		if (adx > ady) {
			//if player is left, move left. Otherwise move right
			if (dx > 0) {
				return 'a';
			}
			else {
				return 'd';
			}
		}
		else { //Move along Y axis
			if (dy > 0) {
				return 'w';
			}
			else {
				return 's';
			}
		}
	}

	//We use another random engine to generate a random number between 0 and 6
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);

	//If we get here, that means the player was further than 5 tiles, so lets just randomly move around
	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0: //left
		return 'a';
	case 1: //up
		return 'w';
	case 2: //down
		return 's';
	case 3: //right
		return 'd';
	default: //no movement
		return '.';
	}

}