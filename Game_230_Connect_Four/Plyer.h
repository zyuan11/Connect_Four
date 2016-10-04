#pragma once
#ifndef PLYER_H_
#define PLYER_H_

class Board;
class Plyer {
	int plyerid;
public:
	void plyerinit(int plyerid_i);
	bool insert(Board& board, int col);
	bool remove(Board& board, int col);
	void op(Board& board);
};
#endif // !PLYER_H_
