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

int game::move(int direction) {
	switch (direction) {
		case 0:
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
			break;
		case 1:
			for (int row = 0; row < this -> board_rows; row++) {
				for (int col = 1; col < this -> board_cols; col++) {
					if (this -> board[row][col] == 0) {
						continue;
					}

					int col_t = col;
					while (col_t > 0) {
						if (this -> board[row][col_t - 1] > 0) {
							break;
						}

						col_t--;
					}


					if (col_t > 0 && this -> board[row][col_t - 1] == this -> board[row][col]) {
						this -> board[row][col_t - 1] *= 2;
						this -> empty++;
						if (this -> max < this -> board[row][col_t - 1]) {
							this -> max = this -> board[row][col_t - 1];
						}
						this -> board[row][col] = 0; 
						continue;
					}

					if (this -> board[row][col_t] == 0) {
						this -> board[row][col_t] = this -> board[row][col];
						this -> board[row][col] = 0;
					}
				}
			}
			break;
		case 2:
			for (int col = 0; col < this -> board_cols; col++) {
				for (int row = this -> board_rows - 2; row >= 0; row--) {
					if (this -> board[row][col] == 0) {
						continue;
					}

					int row_t = row;
					while (row_t < this -> board_rows - 1) {
						if (this -> board[row_t + 1][col] > 0) {
							break;
						}

						row_t++;
					}

					if (row_t < (this -> board_rows - 1) && this -> board[row_t + 1][col] == this -> board[row][col]) {
						this -> board[row_t + 1][col] *= 2;
						this -> empty++;
						if (this -> max < this -> board[row_t + 1][col]) {
							this -> max = this -> board[row_t + 1][col];
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
			break;
		case 3:
			for (int row = 0; row < this -> board_rows; row++) {
				for (int col = this -> board_cols - 2; col >= 0; col--) {
					if (this -> board[row][col] == 0) {
						continue;
					}

					int col_t = col;
					while (col_t < this -> board_cols - 1) {
						if (this -> board[row][col_t + 1] > 0) {
							break;
						}

						col_t++;
					}

					if (col_t < this -> board_cols - 1 && this -> board[row][col_t + 1] == this -> board[row][col]) {
						this -> board[row][col_t + 1] *= 2;
						this -> empty++;
						if (this -> max < this -> board[row][col_t + 1]) {
							this -> max = this -> board[row][col_t + 1];
						}
						this -> board[row][col] = 0; 
						continue;
					}

					if (this -> board[row][col_t] == 0) {
						this -> board[row][col_t] = this -> board[row][col];
						this -> board[row][col] = 0;
					}
				}
			}
			break;
	}

	return this -> turn();
}

int ** game::get_board() {
	return this -> board;
}
