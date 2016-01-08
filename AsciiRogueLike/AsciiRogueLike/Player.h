#pragma once
class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	void setPosition(int x, int y);
	void getPosition(int& x, int& y);

	int attack();
	bool takeDamage(int attack);
	void addExperience(int xp);

private:
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	int _x;
	int _y;
};

