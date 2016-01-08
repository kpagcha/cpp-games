#include <iostream>
#include "TicTacToeGame.h"

using namespace std;

int main()
{
	TicTacToeGame game;

	bool isDone = false;
	char input;

	while (!isDone) {
		game.playGame();
		cout << "Would you like to play again? (Y/N): ";
		cin >> input;

		if (input == 'N' || input == 'n')
			isDone = true;
	}

	system("PAUSE");
}