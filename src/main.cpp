#include "main.h"

int main() {
	console * c = new console();
	game * g = new game();
	c -> print_board(g -> get_board());

	int exit = 0;
	int play = 1;
	while (int ch = c -> event()) {
		int ret = 0;
		switch (ch) {
			case KEY_UP:
				if (! play) {
					break;
				}

				ret = g -> move(0);
				c -> print_board(g -> get_board());
				break;
			case KEY_LEFT:
				if (! play) {
					break;
				}

				ret = g -> move(1);
				c -> print_board(g -> get_board());
				break;
			case KEY_DOWN:
				if (! play) {
					break;
				}

				ret = g -> move(2);
				c -> print_board(g -> get_board());
				break;
			case KEY_RIGHT:
				if (! play) {
					break;
				}

				ret = g -> move(3);
				c -> print_board(g -> get_board());
				break;
			case 'q':
				exit = 1;
				break;
			case 'n':
				play = 1;
				c -> reset();
				g = new game();
				c -> print_board(g -> get_board());
				break;
		}

		c -> debug(g -> get_max());

		if (exit) {
			break;
		}

		if (ret) {
			c -> win();
			play = 0;
		}
	}

	c -> end_console();
}
