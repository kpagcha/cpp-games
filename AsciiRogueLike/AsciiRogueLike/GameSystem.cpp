#include "GameSystem.h"
#include <conio.h>

using namespace std;

GameSystem::GameSystem(string fileName)
{
	_player.init(1, 100, 10, 10, 0);

	_level.load(fileName, _player);
}

void GameSystem::playGame()
{
	bool isDone = false;

	while (!isDone) {
		_level.print();

		playerMove();
		_level.updateEnemies(_player);
	}
}

void GameSystem::playerMove()
{
	char input;

	printf("Enter a new command: ");
	input = _getch();

	_level.movePlayer(input, _player);
}
