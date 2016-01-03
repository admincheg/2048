#include "console.h"

console::console() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();

	this -> debug_w = NULL;
	this -> win_w = newwin(3, 25, 2, 2);
	this -> win_p = new_panel(this -> win_w);
	hide_panel(this -> win_p);
	update_panels();
	mvwprintw(this -> win_w, 1, 1, "You win!" );
	box(this -> win_w, 0, 0);
	doupdate();

	this -> main_w = newwin(14, 30, 1, 1);
	box(this -> main_w, 0, 0);
	this -> panes = (WINDOW***)malloc(sizeof(void*)*4);
	for (int i = 0; i < 4; i++) {
		this -> panes[i] = (WINDOW**)malloc(sizeof(void*)*4);
		for (int j = 0; j < 4; j++) {
			this -> panes[i][j] = derwin(this -> main_w, 3, 6, (i*3)+1, (j*7)+1);
			wrefresh(this -> panes[i][j]);
		}
	}
	wrefresh(this -> main_w);

	refresh();
}

void console::debug(int c) {
	if (this -> debug_w == NULL) {
		this -> debug_w = newwin(3, 25, 15, 1);
	}

	wclear(this -> debug_w);
	box(this -> debug_w, 0, 0);
	mvwprintw(this -> debug_w, 1, 1, "Max number is: %d", c);
	wrefresh(this -> debug_w);
	doupdate();
}

void console::win() {
	show_panel(this -> win_p);
	update_panels();
	wrefresh(this -> win_w);
	doupdate();
}

void console::reset() {
	hide_panel(this -> win_p);
	update_panels();
	wclear(this -> main_w);
	box(this -> main_w, 0, 0);
	wrefresh(this -> main_w);
	doupdate();
	refresh();
}

void console::print_board(int ** board) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			wclear(this -> panes[i][j]);
			box(this -> panes[i][j], 0, 0);
			if (board[i][j] > 0) {
				mvwprintw(this -> panes[i][j], 1, 1, "%d", board[i][j]);
			}
			else {
				mvwprintw(this -> panes[i][j], 1, 1, " ");
			}
			wrefresh(this -> panes[i][j]);
		}
	}

	refresh();
}

int console::event() {
	return getch();
}

void console::end_console() {
	endwin();
}

console::~console() {
	this -> end_console();
}
