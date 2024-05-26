#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#define BLANK " "
#define ARROW ">"
#define ENTER 10

int row = 17;
int col = 24;
int pre_row = 17;

void enterMode(int select) {
	switch (select) {
		case 0:
			printf("start\n");
			break;

		case 1:
			printf("help\n");
			break;
		
		case 2:
			printf("ranking\n");
			break;

		case 3:
			printf("quit\n");
			exit(0);
			break;
	}
}

void showMainView() {
	initscr();
	crmode();
	keypad(stdscr, TRUE);
	noecho();
	clear();
	curs_set(0);

	printf("							     \n");
    	printf("     _____  _   _ ______  _____  _   _  _____  _____  _____  \n");
    	printf("    |_   _|| \\ | ||  ___||_   _|| \\ | ||_   _||_   _||  ___| \n");
    	printf("      | |  |  \\| || |_     | |  |  \\| |  | |    | |  | |__   \n");
    	printf("      | |  | . ` ||  _|    | |  | . ` |  | |    | |  |  __|  \n");
    	printf("     _| |_ | |\\  || |     _| |_ | |\\  | _| |_   | |  | |___  \n");
    	printf("     \\___/ \\_| \\_/\\_|     \\___/ \\_| \\_/ \\___/   \\_/  \\____/  \n");
    	printf("                                                          \n");
    	printf("\n");
    	printf("	 _____  _____   ___   _____ ______  _____ \n");
    	printf("	/  ___||_   _| / _ \\ |_   _|| ___ \\/  ___|\n");
    	printf("	\\ `--.   | |  / /_\\ \\  | |  | |_/ /\\ `--. \n");
    	printf("	 `--. \\  | |  |  _  |  | |  |    /  `--. \\\n");
    	printf("	/\\__/ /  | |  | | | | _| |_ | |\\ \\ /\\__/ /\n");
    	printf("	\\____/   \\_/  \\_| |_/ \\___/ \\_| \\_|\\____/ \n");
    	printf("                                            \n");
    	printf("                                            \n");
    	printf("                       >  START		        \n");
    	printf("                          HELP         		\n");
    	printf("                          RANKING			\n");
    	printf("                          QUIT 			\n");
    	printf("							\n");
    	printf("							\n");
    	printf("							\n");
	
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
				change = (change == 0) ? 3 : -1;
				row = pre_row + change;
				select = row - 17;
				move(pre_row, col);
				addstr(BLANK);
				move(row, col);
				addstr(ARROW);
				break;

			case KEY_DOWN:
				change = (change == 3) ? -3 : 1;
				row = pre_row + change;
				select = row - 17;
				move(pre_row, col);
				addstr(BLANK);
				move(row, col);
				addstr(ARROW);
				break;

			case ENTER:
				enterMode(select);
				break;
		}
	}
	endwin();
}
