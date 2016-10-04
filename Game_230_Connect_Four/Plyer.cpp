#include "Plyer.h"
#include "Board.h"
#include <iostream>
using namespace std;

void Plyer::plyerinit(int plyerid_i) {
	plyerid = plyerid_i;
}

bool Plyer::insert(Board& board, int col_i) {
	int col = col_i - 1;
	int row = 6;
	while (board.Arr2d[row][col] != '.' && row >= 1) {
		row--;
	}
	if (row == 0) {
		cout << "The column is full." << endl;
		return false;
	}
	else if (row >= 1 && row <= 6) {
		if (plyerid == 1) {
			board.Arr2d[row][col] = 'X';
		}
		else if (plyerid == 2) {
			board.Arr2d[row][col] = 'O';
		}
		board.lastrow = row;
		board.lastcol = col;
		return true;
	}
}

bool Plyer::remove(Board& board, int col_i) {
	int col = col_i - 1;
	int row = 6;
	if (board.Arr2d[row][col] == '.') {
		cout << "No piece in this column so far." << endl;
		return false;
	}
	else if ((board.Arr2d[row][col] == 'X' && plyerid == 2) || (board.Arr2d[row][col] == 'O' && plyerid == 1)) {
		cout << "You cannot remove your opponent's piece" << endl;
		return false;
	}
	else if ((board.Arr2d[row][col] == 'X' && plyerid == 1) || (board.Arr2d[row][col] == 'O' && plyerid == 2)) {
		while (board.Arr2d[row][col] != '.' && board.Arr2d[row][col] != char(col + 48 + 1)) {
			if (row == 1) {
				board.Arr2d[row][col] = '.';
			}
			else if (row > 1) {
				board.Arr2d[row][col] = board.Arr2d[row - 1][col];
			}
			row--;
		}
	}
	board.lastrow = 0;
	board.lastcol = col;
	return true;
}

void Plyer::op(Board& board) {
	char i_d;
	int col;

	//game mode does not allow piece removing action
	if (board.gamemode == 1 || board.gamemode == 4) {
		if (plyerid == 1) {
			cout << "Player X's turn! Enter the column number to insert a piece: ";
		}
		else if (plyerid == 2) {
			cout << "Player O's turn! Enter the column number to insert a piece: ";
		}
		cin >> col;
		cout << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');


		if (col >= 1 && col <= 7) {
			if (!insert(board, col)) {
				op(board);
			}
		}
		else {
			cout << "The column you selected is out of boundary. Make a selection from 1 to 7" << endl;
			op(board);
		}
	}
	//game mode allows piece removing action
	else if (board.gamemode == 2 || board.gamemode == 3) {
		if (plyerid == 1) {
			cout << "Player X's turn! Enter I/D to insert or delete a piece: ";
		}
		else if (plyerid == 2) {
			cout << "Player O's turn! Enter I/D to insert or delete a piece: ";
		}
		cin >> i_d;
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		if (i_d == 'i' || i_d == 'I' || i_d == 'd' || i_d == 'D') {
			cout << "\nEnter the column number to insert or delete a piece: ";
			cin >> col;
			cout << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			if (col >= 1 && col <= 7) {
				if (i_d == 'D' || i_d == 'd') {
					if (!remove(board, col)) {
						op(board);
					}
				}
				else if (i_d == 'I' || i_d == 'i') {
					if (!insert(board, col)) {
						op(board);
					}
				}
			}
			else {
				cout << "The column you selected is out of boundary. Make a selection from 1 to 7" << endl;
				op(board);
			}
		}
		else {
			cout << "You can only enter i/d or I/D to choose to insert or delete a piece" << endl;
			op(board);
		}
	}


}