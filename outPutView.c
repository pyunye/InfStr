#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "textmanager.h"

#define BLANK " "
#define ARROW ">"
#define STAIR "_"
#define ENTER 10
#define BACKKEY "> back key 'b'\n\n"

int row = 17;
int col = 23;
int pre_row = 17;
int prt_row = 0; // print row

void showPlayingView();
void printHelp();
void printRank();
void showScore(int score, int col);

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
	
	int prt_row = 0;
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

void printHelp(char text[]){
	initscr();
	noecho();
	clear();
	addstr(text);
	addstr(BACKKEY);
	refresh();
}

void printRank(Players unit){
	initscr();
	noecho();
	clear();
	char playersInfo[256];
	int i;
	while(i < unit.size && i < 10){
		sprintf(playersInfo, " Rank %d : %d(%s)\n", i+1, unit.members[i].score, unit.members[i].username);
		addstr(playersInfo);
		i++;
	}
	addstr("\n");
	addstr(BACKKEY);
	refresh();
}

void showPlayingView() {
	
	initscr();
	crmode();
	noecho();

	int score = 0;
	char score[100] = { 0 };
	move(1, 60);
	addstr(score);

	int stairs[MAX_QUEUE_SIZE];
	stairs = getStairDir();

	while(1) {
		printStairs(stairs);
		int key = getch();
		if(isCorrectDirection(key)) {
			clearStairs(stairs);
			score += 10;
			move(1, 60);
			addstr(score);
		}
		else {
			showGameOverView(score);				
		}

		refresh();
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


void showScore(int score, int col);

void showGameOverView(int score) {
	initscr();
        crmode();
        noecho();
	clear();
	
	move(5, 0);
	prt_row = 5;

	add("         ######      ####    ##       ## ########              #####    ##       ##  #######  #######        ###       "); 
        add("       ##     ##    ##  ##   ###    #### ##                  ###   ###  ##       ##  ##       ##    ##       ###       ");
        add("      ##           ##    ##  ## ## ## ## ##                 ##       ## ##       ##  ##       ##    ##       ###       ");
        add("      ##    ##### ########## ##  ###  ## ########           ##       ##  ##     ##   #######  #######        ###       ");
        add("      ##      ##  ##      ## ##       ## ##                 ##       ##   ##   ##    ##       ##    ##       ###       ");
        add("       ##     ##  ##      ## ##       ## ##                  ###   ###     ## ##     ##       ##     ##                ");
        add("        #######   ##      ## ##       ## ########              #####        ###      #######  ##      ##     ###       ");
                     
	prt_row = 20;
	move(20, 0);
	add("  ######    ######     #####     ######     ########            ");
        add(" ##    ##  ##        ###   ###   ##    ##   ##                  ");
        add(" ##       ##        ##       ##  ##    ##   ##            ##    ");
        add("  #####   ##        ##       ##  ######     ########            ");
        add("       ## ##        ##       ##  ##    ##   ##            ##    ");
        add(" ##    ##  ##        ###   ###   ##     ##  ##                  ");
        add("  ######    ######     #####     ##      ## ########            ");

	int score_len = 0;
	int score_num = score;	
	int score_col = 12;

	while (score_num != 0) {
		score_len++;
		score_num /= 10;
	}
	
	for(int i = 0; i < score_len; i++) {
		showScore(score % 10, 64 + score_col); 
		score /= 10;
		score_col *= 2;
	}	

	refresh();
}

void showScore(int score, int col) {

	switch(score) {
		case 0:
			mvprintw(20, col, "    ####    ");
			mvprintw(21, col, "  ##    ##  ");
     	                mvprintw(22, col, " ##      ## ");
			mvprintw(23, col, " ##      ## ");
			mvprintw(24, col, " ##      ## ");
			mvprintw(25, col, "  ##    ##  ");
			mvprintw(26, col, "    ####    ");
									 
		case 1:
			mvprintw(20, col, "     ###    ");
                        mvprintw(21, col, "    ####    ");
			mvprintw(22, col, "  ##  ##    ");
	                mvprintw(23, col, "      ##    ");
	                mvprintw(24, col, "      ##    ");
	                mvprintw(25, col, "      ##    ");
			mvprintw(26, col, "  ######### ");

		case 2:
			mvprintw(20, col, "   ######   ");
			mvprintw(21, col, "  ##    ##  ");
			mvprintw(22, col, "       ###  ");
			mvprintw(23, col, "      ###   ");
			mvprintw(24, col, "    ###     ");
			mvprintw(25, col, "  ###       ");
			mvprintw(26, col, " ########## ");
				
		case 3:
			mvprintw(20, col, "   ######   ");
			mvprintw(21, col, " ###    ### ");
			mvprintw(22, col, "        ### ");
			mvprintw(23, col, "     ####   ");
			mvprintw(24, col, "        ### ");
			mvprintw(25, col, " ###    ### ");
			mvprintw(26, col, "   ######   ");
				
		case 4:               
                        mvprintw(20, col, "     ####   ");
                        mvprintw(21, col, "    ## ##   ");
                        mvprintw(22, col, "   ##  ##   ");
                        mvprintw(23, col, "  ##   ##   ");
                        mvprintw(24, col, " ########## ");
                        mvprintw(25, col, "       ##   ");
                        mvprintw(26, col, "       ##   ");
										
		case 5:		
                        mvprintw(20, col, " ########## ");
                        mvprintw(21, col, " ##         ");
                        mvprintw(22, col, " ##         ");
                        mvprintw(23, col, " #########  ");
                        mvprintw(24, col, "         ## ");
                        mvprintw(25, col, "         ## ");
                        mvprintw(26, col, " #########  ");

                case 6:
                        mvprintw(20, col, "  ########  ");
                        mvprintw(21, col, " ##      ## ");
                        mvprintw(22, col, " ##         ");
                        mvprintw(23, col, " #########  ");
                        mvprintw(24, col, " ##      ## ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, "  ########  ");

                case 7:
                        mvprintw(20, col, " ########## ");
                        mvprintw(21, col, "        ##  ");
                        mvprintw(22, col, "       ##   ");
                        mvprintw(23, col, "      ##    ");
                        mvprintw(24, col, "     ##     ");
                        mvprintw(25, col, "    ##      ");
                        mvprintw(26, col, "   ##       ");

                case 8:
                        mvprintw(20, col, "  ########  ");
                        mvprintw(21, col, " ##      ## ");
                        mvprintw(22, col, " ##      ## ");
                        mvprintw(23, col, "  ########  ");
                        mvprintw(24, col, " ##      ## ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, "  ########  ");

                case 9:
                        mvprintw(20, col, "  #######  ");
                        mvprintw(21, col, " ##     ## ");
                        mvprintw(22, col, " ##     ## ");
                        mvprintw(23, col, "  #######  ");
                        mvprintw(24, col, "      ##   ");
                        mvprintw(25, col, "     ##    ");
                        mvprintw(26, col, "    ##     ");

				
		}   
}
