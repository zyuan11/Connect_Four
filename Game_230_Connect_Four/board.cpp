#include "Board.h"

void Board::modeselect() {
	int mode;
	cout << "Make a selection of game mode from 1, 2, 3, 4. (1 for allowing wrapping-around successonly; 2 for allowing piece removing action only; 3 for both; 4 for none)";
	cin >> mode;
	cout << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (mode == 1 || mode == 2 || mode == 3 || mode == 4) {
		gamemode = mode;
	}
	else {
		cout << "You can only select from 1 to 4" << endl;
		modeselect();
	}

}
void Board::init() {
	int cnt = 1;
	while (cnt <= 7) {
		Arr2d[0][cnt - 1] = char(48 + cnt);
		cnt++;
	}
	for (int row = 1; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			Arr2d[row][col] = char(46);
		}
	}
	modeselect();
	f_clear = true;
}

void Board::display() {
	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			cout << Arr2d[row][col];
		}
		cout << endl;
	}
}

void Board::declarewin(char plymk) {
	if (plymk == 'X') {
		cout << "Player X wins the game!" << endl;
	}
	else if (plymk == 'O') {
		cout << "Player O wins the game!" << endl;
	}
	else if (plymk == 'D') {
		cout << "Draw!!" << endl;
	}
	newgamechk();
}

void Board::newgamechk() {
	char y_n;
	cout << "Enter y/n (yes/no) to decide if you want to start a new game. ";
	cin >> y_n;
	cout << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (y_n == 'y') {
		f_newgame = true;
	}
	else if (y_n == 'n') {
		f_newgame = false;
	}
	else {
		cout << "You have to make a selection between y/n (yes/no)." << endl;
		newgamechk();
	}
}

bool Board::checkdraw() {
	for (int col = 0; col <= 6; col++) {
		if (Arr2d[1][col] == '.') {
			return false;
		}
	}
	return true;
}
void Board::go(int godir) {
	char plymk = Arr2d[lastrow][lastcol];
	bool f_wrap = gamemode == 1 || gamemode == 3;
	firstrow = lastrow;
	firstcol = lastcol;

	switch (godir) {
	case 1:	//horzentally go left to find the closest same player marker
			//wrap around success mode
		if (f_wrap) {
			while (Arr2d[firstrow][firstcol] == plymk) {
				if (firstcol == 0) {
					firstcol = 6;
				}
				else {
					firstcol--;
				}
			}
			if (Arr2d[firstrow][firstcol] != plymk) {
				if (firstcol == 6) {
					firstcol = 0;
				}
				else {
					firstcol++;
				}
			}
		}
		//not wrap around success mode
		else if (!f_wrap) {
			while (firstcol >= 0 && Arr2d[firstrow][firstcol] == plymk) {
				firstcol--;
			}
			//check different plymk break
			if (Arr2d[firstrow][firstcol] != plymk) {
				firstcol++;
			}
		}
		break;
	case 2:	//diagonally go up left to find the closest same player marker
			//wrap around mode
		if (f_wrap) {
			while (firstrow >= 1 && Arr2d[firstrow][firstcol] == plymk) {
				//point inside
				if (firstcol > 0) {
					firstcol--;
				}
				//point on the left boundary
				else if (firstcol == 0) {
					firstcol = 6;
				}
				firstrow--;
			}
			if (Arr2d[firstrow][firstcol] != plymk) {
				if (firstcol == 6) {
					firstcol = 0;
				}
				else {
					firstcol++;
				}
				firstrow++;
			}
		}
		//not wrap around mode
		else if (!f_wrap) {
			while (firstrow >= 1 && firstcol >= 0 && Arr2d[firstrow][firstcol] == plymk) {
				firstcol--;
				firstrow--;
			}

			if (Arr2d[firstrow][firstcol] != plymk) {
				firstcol++;
				firstrow++;
			}
		}
		break;
	case 3: //vertically go up to find the closest same player marker
		while ((firstrow >= 1 && Arr2d[firstrow][firstcol] == plymk)) {
			firstrow--;
		}

		if (Arr2d[firstrow][firstcol]) {
			firstrow++;
		}
		break;
	case 4: //diagonally go up right to find the closest same player marker
			//wrap around success mode
		if (f_wrap) {
			while (firstrow >= 1 && Arr2d[firstrow][firstcol] == plymk) {
				//point inside
				if (firstcol < 6) {
					firstcol++;
				}
				//point on the right boundary
				else if (firstcol == 6) {
					firstcol = 0;
				}
				firstrow--;
			}
			if (Arr2d[firstrow][firstcol] != plymk) {
				if (firstcol == 0) {
					firstcol = 6;
				}
				else {
					firstcol--;
				}
				firstrow++;
			}
		}
		//not wrap around success mode
		else if (!f_wrap) {
			while ((firstrow >= 1) && firstcol <= 6 && (Arr2d[firstrow][firstcol] == plymk)) {
				firstcol++;
				firstrow--;
			}

			if (Arr2d[firstrow][firstcol] != plymk) {
				firstcol--;
				firstrow++;
			}
		}
		break;
	}
}

bool Board::back(int bckdir) {
	int		cntTW = 0;
	char	plymk = Arr2d[firstrow][firstcol];
	bool	f_wrap = gamemode == 1 || gamemode == 3;
	switch (bckdir) {
	case 1:	//horzentally go right to find how many player markers in the line
			//wrap around success mode
		if (f_wrap) {
			while ((cntTW < 4) && (Arr2d[firstrow][firstcol] == plymk)) {
				if (firstcol == 6) {
					firstcol = 0;
				}
				else {
					firstcol++;
				}
				cntTW++;
			}
		}
		//not wrap around success mode
		else if (!f_wrap) {
			while (firstcol <= 6 && (cntTW < 4) && (Arr2d[firstrow][firstcol] == plymk)) {
				firstcol++;
				cntTW++;
			}
		}
		break;
	case 2:	//diagonally go down right to find how many player markers in the line
			//wrap around success mode
		if (f_wrap) {
			while ((firstrow <= 6) && (cntTW < 4) && (Arr2d[firstrow][firstcol] == plymk)) {
				//point inside
				if (firstcol < 6) {
					firstcol++;
				}
				//point on the right boundary
				else if (firstcol == 6) {
					firstcol = 0;
				}
				firstrow++;
				cntTW++;
			}
		}
		//not wrap around success mode
		else if (!f_wrap) {
			while ((firstrow <= 6) && firstcol <= 6 && (cntTW < 4) && (Arr2d[firstrow][firstcol] == plymk)) {
				firstcol++;
				firstrow++;
				cntTW++;
			}
		}
		break;
	case 3: //vertically go down to find how many player markers in the line
		while ((firstrow <= 6) && (cntTW < 4) && (Arr2d[firstrow][firstcol] == plymk)) {
			firstrow++;
			cntTW++;
		}
		break;
	case 4: //diagonally go down left to find how many player markers in the line
			//wrap around success mode
		if (f_wrap) {
			while ((firstrow <= 6) && cntTW < 4 && (Arr2d[firstrow][firstcol] == plymk)) {
				//point inside
				if (firstcol > 0) {
					firstcol--;
				}
				//point on the left boundary
				else if (firstcol == 0) {
					firstcol = 6;
				}
				firstrow++;
				cntTW++;
			}
		}
		//not wrap around success mode
		else if (!f_wrap) {
			while ((firstrow <= 6) && firstcol >= 0 && cntTW < 4 && (Arr2d[firstrow][firstcol] == plymk)) {
				firstcol--;
				firstrow++;
				cntTW++;
			}
		}
		break;
	}

	if (cntTW == 4) {
		declarewin(plymk);
		return true;
	}
	else if (checkdraw()) {
		declarewin('D');
		return true;
	}
	else {
		return false;
	}

}

bool Board::pointcheck() {
	for (int i = 1; i <= 4; i++) {
		go(i);
		if (back(i)) {
			return true;
			break;
		}
	}
	return false;
}
bool Board::check() {
	//last operation is remove
	if (lastrow == 0) {
		for (int i = 6; i > 0; i--) {
			lastrow = i;
			if (Arr2d[lastrow][lastcol] == '.') {
				return false;
			}
			if (pointcheck()) {
				return true;
			}
		}
	}
	//last operation is insert
	else {
		return pointcheck();
	}
	return false;
}

