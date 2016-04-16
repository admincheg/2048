#include "game.h"

game::game() {
	struct timeval t;
	gettimeofday(&t, NULL);
	int seed = (t.tv_sec / 1000) + (t.tv_usec * 10000);
	srand(seed);

	this -> board = (int**)calloc(this -> board_rows, sizeof(void*));
	for (int i = 0; i < this -> board_rows; i++) {
		this -> board[i] = (int*)calloc(this -> board_cols, sizeof(int));
	}

	this -> max = 0;
	this -> empty = this -> board_rows * this -> board_cols;
	this -> turn();
}

int game::get_max() {
	return this -> max;
}

int game::turn() {
	if (this -> max >= 2048) {
		return 1;
	}

	for (int i = 0; i < 2; i++) {
		int row, col;
		do {
			int r = rand() % (this -> board_rows * this -> board_cols);
			row = r / this -> board_rows;
			col = r % this -> board_rows;
		} while (! this -> set_cell(row, col, 2) && this -> has_empty());
	}

	return 0;
}

bool game::is_empty(int row, int col) {
	if (this -> board[row][col] > 0) {
		return false;
	}

	return true;
}

bool game::set_cell(int row, int col, int value) {
	if (this -> is_empty(row, col)) {
		this -> board[row][col] = value;
		this -> empty--;
		return true;
	}

	return false;
}

bool game::has_empty() {
	if (this -> empty < 1) {
		return false;
	}

	return true;
}

void game::print_board() {
	for (int i = 0; i < this -> board_rows; i++) {
		for (int j = 0; j < this -> board_cols; j++) {
			std::cout << (int)this -> board[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void game::rotate_board(bool reverse) {
	int width = this -> board_cols;

	for (int i = 0; i < (width / 2); i++) {
		int offsetRow = width - i - 1;

		for (int j = i; j < (width - 1 - i); j++) {
			int offsetCol = width - j - 1;

			int tmp = this -> board[i][j];
			if (reverse) {
				this -> board[i][j] = this -> board[j][offsetRow];
				this -> board[j][offsetRow] = this -> board[offsetRow][offsetCol];
				this -> board[offsetRow][offsetCol] = this -> board[offsetCol][i];
				this -> board[offsetCol][i] = tmp;
			}
			else {
				this -> board[i][j] = this -> board[offsetCol][i];
				this -> board[offsetCol][i] = this -> board[offsetRow][offsetCol];
				this -> board[offsetRow][offsetCol] = this -> board[j][offsetRow];
				this -> board[j][offsetRow] = tmp;
			}
		}
	}
}

void game::compute() {
	for (int col = 0; col < this -> board_cols; col++) {
		for (int row = 1; row < this -> board_rows; row++) {
			if (this -> board[row][col] == 0) {
				continue;
			}

			int row_t = row;
			while (row_t > 0) {
				if (this -> board[row_t - 1][col] > 0) {
					break;
				}

				row_t--;
			}


			if (row_t > 0 && this -> board[row_t - 1][col] == this -> board[row][col]) {
				this -> board[row_t - 1][col] *= 2;
				this -> empty++;
				if (this -> max < this -> board[row_t - 1][col]) {
					this -> max = this -> board[row_t - 1][col];
				}
				this -> board[row][col] = 0; 
				continue;
			}

			if (this -> board[row_t][col] == 0) {
				this -> board[row_t][col] = this -> board[row][col];
				this -> board[row][col] = 0;
			}
		}
	}
}

int game::move(int direction) {
	switch (direction) {
		case 0:
			this -> compute();
			break;
		case 1:
			this -> rotate_board(false);
			this -> compute();
			this -> rotate_board(true);
			break;
		case 2:
			this -> rotate_board(false);
			this -> rotate_board(false);
			this -> compute();
			this -> rotate_board(false);
			this -> rotate_board(false);
			break;
		case 3:
			this -> rotate_board(true);
			this -> compute();
			this -> rotate_board(false);
			break;
	}

	return this -> turn();
}

int ** game::get_board() {
	return this -> board;
}
