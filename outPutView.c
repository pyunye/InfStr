#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#define BLANK " "
#define ARROW ">"
#define ENTER 10

int row = 17;
int col = 23;
int pre_row = 17;
int prt_row = 0; // print row of main view

void enterMode(int select) {
	switch (select) {
		case 0:
			initscr();
			move(30, 24);
			addstr("start");
			break;

		case 1:
			initscr();
			move(30, 24);
			addstr("help");
			break;
		
		case 2:
			initscr();
			move(30, 24);
			addstr("ranking");
			break;

		case 3:
			initscr();
			move(30, 24);
			addstr("quit");
			exit(0);
			break;
	}
}

void add(char * message) {
	addstr(message);
	prt_row++;
	move(prt_row, 0);
}

void showMainView() {
	initscr();
	crmode();
	keypad(stdscr, TRUE);
	noecho();
	clear();
	curs_set(0);
	
	move(0, 0);
	add("                                                               ");
    	add("     _____  _   _ ______  _____  _   _  _____  _____  _____    ");
    	add("    |_   _|| \\ | ||  ___||_   _|| \\ | ||_   _||_   _||  ___| ");
    	add("      | |  |  \\| || |_     | |  |  \\| |  | |    | |  | |__   ");
    	add("      | |  | . ` ||  _|    | |  | . ` |  | |    | |  |  __|    ");
    	add("     _| |_ | |\\  || |     _| |_ | |\\  | _| |_   | |  | |___  ");
    	add("     \\___/ \\_| \\_/\\_|     \\___/ \\_| \\_/ \\___/   \\_/  \\____/  ");
    	add("                                                               ");
    	add("                                                               ");
    	add("	 _____  _____   ___   _____ ______  _____                   ");
    	add("	/  ___||_   _| / _ \\ |_   _|| ___ \\/  ___|                ");
    	add("	\\ `--.   | |  / /_\\ \\  | |  | |_/ /\\ `--.               ");
    	add("	 `--. \\  | |  |  _  |  | |  |    /  `--. \\                ");
    	add("	/\\__/ /  | |  | | | | _| |_ | |\\ \\ /\\__/ /              ");
    	add("	\\____/   \\_/  \\_| |_/ \\___/ \\_| \\_|\\____/            ");
    	add("                                                               ");
    	add("                                                               ");
    	add("                       >  START		                    ");
    	add("                          HELP         		            ");
    	add("                          RANKING			            ");
    	add("                          QUIT 			            ");
    	add("							            ");
    	add("							            ");
    	add("							            ");
	
	refresh();
}

void setSelectionCursor() {

	int key;
	int change = 0;
	int select = 0;
	
	while(1)
	{
		key = getch();

		switch(key) {
			case KEY_UP:
				change = (select == 0) ? 3 : -1;
				row = pre_row + change;
				select = row - 17;
				move(pre_row, col);
				addstr(BLANK);
				move(row, col);
				addstr(ARROW);
				pre_row = row;
				break;

			case KEY_DOWN:
				change = (select == 3) ? -3 : 1;
				row = pre_row + change;
				select = row - 17;
				move(pre_row, col);
				addstr(BLANK);
				move(row, col);
				addstr(ARROW);
				pre_row = row;
				break;

			case ENTER:
				enterMode(select);
				break;
		}
	}
	endwin();
}

int main() {
	showMainView();
	setSelectionCursor();
}
