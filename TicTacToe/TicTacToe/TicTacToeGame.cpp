#include "TicTacToeGame.h"
#include <iostream>

using namespace std;

TicTacToeGame::TicTacToeGame()
{
}

void TicTacToeGame::playGame()
{
	clearBoard();

	char player1 = 'X';
	char player2 = 'O';

	char currentPlayer = player1;
	bool isDone = false;

	int x, y;

	int turn = 0;

	while (!isDone) {
		printBoard();

		x = getXCoord();
		y = getYCoord();

		if (!placeMarker(x, y, currentPlayer))
			cout << "That spot is occupied!" << endl;
		else {
			turn++;

			if (checkForVictory(currentPlayer)) {
				cout << "The game is over! Player " << currentPlayer << " has won!" << endl;
				isDone = true;
			}
			else if (turn == 9) {
				cout << "It's a tie game!" << endl;
				isDone = true;
			}

			if (currentPlayer == player1)
				currentPlayer = player2;
			else
				currentPlayer = player1;
		}
	}
}

int TicTacToeGame::getXCoord()
{
	bool isInputBad = true;
	int x;

	while (isInputBad) {
		cout << "Enter the X coodinate: ";
		cin >> x;

		if (x < 1 || x > 3)
			cout << "Invalid coordinate" << endl;
		else
			isInputBad = false;
	}
	
	return x - 1;
}

int TicTacToeGame::getYCoord()
{
	bool isInputBad = true;
	int y;

	while (isInputBad) {
		cout << "Enter the Y coodinate: ";
		cin >> y;

		if (y < 1 || y > 3)
			cout << "Invalid coordinate" << endl;
		else
			isInputBad = false;
	}

	return y - 1;
}

bool TicTacToeGame::placeMarker(int x, int y, char currentPlayer)
{
	if (board[y][x] != ' ')
		return false;

	board[y][x] = currentPlayer;
}

bool TicTacToeGame::checkForVictory(char currentPlayer)
{
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == currentPlayer && board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return true;
		if (board[i][0] == currentPlayer && board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return true;
	}

	if (board[0][0] == currentPlayer && board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return true;

	if (board[0][2] == currentPlayer && board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return true;

	return false;
}

void TicTacToeGame::clearBoard()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = ' ';
}

void TicTacToeGame::printBoard()
{
	cout << endl;
	cout << " |1 2 3|\n";
	cout << " -------\n";
	for (int i = 0; i < 3; i++) {
		cout << i + 1 << "|" << board[i][0] << "|" << board[i][1] << "|" << board[i][2] << "|" << endl;
		cout << " -------\n";
	}
}