#include "GameSystem.h"
#include <iostream>
#include <conio.h>


//Constructor sets up the game
GameSystem::GameSystem(string levelFileName) {

	//Initialize the player properties. TODO: Load and save from a save file
	_player.init(1, 100, 10, 10, 0);

	//Load the level from file
	_level.load(levelFileName, _player);

	printf("%s was loaded!\n", levelFileName.c_str());
	printf("\n*Be sure to make your console window bigger for the best experience.\n\n");
	system("PAUSE");
}

void GameSystem::playGame() {

	bool isDone = false;

	while (isDone != true) {
		//playerMove prints "Enter a move command" so we tell the level about it so it can format
		_level.setNumPrints(1);
		//print the board
		_level.print();
		//get player input
		playerMove();
		//update level AI
		_level.updateEnemies(_player);
	}
}

//Player input
void GameSystem::playerMove() {
	char input;
	printf("Enter a move command (w/s/a/d): ");
	input = _getch();

	_level.movePlayer(input, _player);

}