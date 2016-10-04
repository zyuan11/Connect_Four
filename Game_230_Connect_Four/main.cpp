#include "Board.h"
#include "Plyer.h"
#include <iostream>
using namespace std;

int main() {
	Board	board;
	Plyer	plyer1, plyer2;
	int		f_done = false;
	char	y_n;

	board.f_newgame = true;
	plyer1.plyerinit(1);
	plyer2.plyerinit(2);

	while (board.f_newgame) {
		board.init();
		board.display();
		while (!f_done) {
			plyer1.op(board);
			board.display();
			if (board.check()) {
				break;
			}
			plyer2.op(board);
			board.display();
			f_done = board.check();
		}
		f_done = false;
	}


	system("pause");
	return 0;
}