#pragma once

#ifndef BOARD_H_
#define BOARD_H_

using namespace std;
#include <iostream>;

class Board {
private:
	int		firstrow;	//the row index to track the checking point
	int		firstcol;	//the col index to track the checking point
public:
	int		gamemode;   //1 for allowing wrapping-around successonly; 2 for allowing piece removing action only; 3 for both; 4 for none
	char	Arr2d[7][7];	//board
	int		lastrow;		//the row index of the last inserted point, lastrow == 0 if the last operation is delete
	int		lastcol;		//the row index of the last inserted point
	bool	f_clear;		//true if the board is empty, false if not
	bool	f_newgame;		//true if player want to start a new game, false if not
	void	modeselect();
	void	init();			//initialize the board
	void	display();		//display the board
	void	declarewin(char plymk);
	void	newgamechk();
	bool	checkdraw();
	void	go(int godir);
	bool	back(int bckdir);
	bool	pointcheck();
	bool	check();

};
#endif