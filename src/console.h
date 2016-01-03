#ifndef CONSOLE_H
#define CONSOLE_H 1

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <panel.h>

class console {
	public:
		console();
		~console();
		void end_console();
		void print_board(int ** board);
		int event();
		void win();
		void debug(int c);
		void reset();
	private:
		WINDOW *** panes;
		WINDOW * main_w;
		WINDOW * win_w;
		WINDOW * debug_w;
		PANEL * win_p;
};

#endif
