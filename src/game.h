#ifndef GAME_H
#define GAME_H 1

#include <iostream>
#include <sys/time.h>
#include <stdlib.h>

class game {
	public:
		game();
		bool set_cell(int row, int col, int value);
		bool is_empty(int row, int col);
		int move(int direction);
		void print_board();
		int ** get_board();
		int get_max();

	private:
		int ** board;
		int turn();
		void rotate_board(bool reverse);
		void compute();
		static const int board_rows = 4;
		static const int board_cols = 4;
		int empty;
		int max;
		bool has_empty();
};

#endif
