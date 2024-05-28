#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "textmanager.h"
#include "stair.h"

#define BLANK " "
#define ARROW ">"
#define STAIR "_"
#define ENTER 10
#define BACKKEY "> back key 'b'\n\n"


int row = 17;
int col = 23;
int pre_row = 17;
int prt_row = 0; // print row of main view

void showPlayingView();
void printHelp();
void printRank();

void enterMode(int select) {
	switch (select) {
		case 0:
			initscr();
			clear();
			move(30, 24);
			addstr("start");
			break;

		case 1:
			printHelp();
			break;
		
		case 2:
			printRank();
			break;

		case 3:
			initscr();
			clear();
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

void printHelp(){
	char helpText[512] = "<<<<<	Help : Infinite Stair	  >>>>>\n\n* Press left or right to move upstair!\n* If you do not press any button for a long time or press a wrong button, game is over.\n* If you get a coin, you can press the button slowly.\n\n";
	initscr();
	noecho();
	clear();
	addstr(helpText);
	addstr(BACKKEY);
	refresh();
	while(getch() != 'b'){
	}
}

void printRank(){
	Player *players = scoreOutput();
	initscr();
	noecho();
	clear();
	int i = 1;
	char playersInfo[256];
	while(i <= 10 && players[i].username[0] != '\0'){
		sprintf(playersInfo, " Rank %d : %d(%s)\n", i, players[i].score, players[i].username);
		addstr(playersInfo);
		i++;
	}
	addstr("\n");
	addstr(BACKKEY);
	while(getch() != 'b'){
	}
}

void showPlayingView() {
	
	initscr();
	crmode();
	noecho();

	move(0, 0);
	add("                                                                 ");
	add("              ================================================== ");
	add("             |//////////////////////////////////////////////////|");
	add("             |//////////////////////////////////////////////////|");
	add("              ================================================== ");
	move(25, 40);
	add("o");
	
	int score = 0;
	char score[100] = { 0 };
	move(1, 60);
	addstr(score);
	refresh();

	int stairs[MAX_QUEUE_SIZE];
	stairs = getStairDir();

	while(1) {
		printStairs(stairs);
		int key = getch();
		if(isCorrectDirection(key)) {
			clearStairs(stairs);
			push(stair);  // ??
			score += 10;
			move(1, 60);
			addstr(score);
		}
		else {
				
		}
	}
	
}

void printStairs(int stairs[]) {

	int stairs[MAX_QUEUE_SIZE];
	stairs = getStairDir();
	int stair_col = 40;

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (stairs[i] == KEY_LEFT) {
			move(25-i-1, --stair_col);
			addstr(STAIR);
		} else if (stairs[i] == KEY_RIGHT) {
			move(25-i-1, ++stair_col);
			addstr(STAIR);
		}
	}
}

void clearStairs(int stairs[]) {

	int stairs[MAX_QUEUE_SIZE];
	stairs = getStairDir();
	int clear_col = 40;

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (stairs[i] == KEY_LEFT) {
			move(25-i-1, --clear_col);
			addstr(BLANK);
		} else if (stairs[i] == KEY_RIGHT) {
			move(25-i-1, ++clear_col);
			addstr(BLANK);
		}
	}
}
