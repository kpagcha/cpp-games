#pragma once
#include "Player.h"
#include "Level.h"
#include <string>

class GameSystem
{
public:
	GameSystem(std::string fileName);
	
	void playGame();
	void playerMove();

private:
	Player _player;
	Level _level;
};