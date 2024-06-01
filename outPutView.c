#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "outPutView.h"
#include "stairs.h"

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

void add(char * message) {
	addstr(message);
	prt_row++;
	move(prt_row, 0);
}

void showMainView() {
	
	clear();
        prt_row = 0;
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

void setSelectionCursor(int select) {
	static int old_select = 0;
	
	switch (old_select) {
		case 0:
			move(17, 23);
			break;
		case 1:
			move(18, 23);
			break;
		case 2:
			move(19, 23);
			break;
		case 3:
			move(20, 23);
			break;

	}
	addstr(BLANK);

	old_select = select;
	switch (select) {
		case 0:
			move(17, 23);
			break;
		case 1:
			move(18, 23);
			break;
		case 2:
			move(19, 23);
			break;
		case 3:
			move(20, 23);
			break;
	}
	addstr(ARROW);
	refresh();
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
	move(1, 60);
	addstr(score);

	int stairs[MAX_QUEUE_SIZE];
	stairs = getStairsDir();

	while(1) {
		printStairs(stairs);
		clearStairs(stairs);
		move(1, 60);
		addstr(score);
		refresh();
		}	
}

void printStairs(int stairs[]) {
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

	add("    ######    ######     #####     ######     ########            ");
        add("   ##    ##  ##        ###   ###   ##    ##   ##                  ");
        add("   ##       ##        ##       ##  ##    ##   ##            ##    ");
        add("    #####   ##        ##       ##  ######     ########            ");
        add("         ## ##        ##       ##  ##    ##   ##            ##    ");
        add("   ##    ##  ##        ###   ###   ##     ##  ##                  ");
        add("    ######    ######     #####     ##      ## ########            ");

	int score_len = 0;
	int score_num = score;	
	int score_col = 12;

	while (score_num != 0) {
		score_len++;
		score_num /= 10;
	}
	
	for(int i = score_len - 1; i >= 0; i--) {
		showScore(score % 10, 65 +  i * score_col); 
		score /= 10;
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
			break;						 
			
		case 1:
			mvprintw(20, col, "     ###    ");
                        mvprintw(21, col, "    ####    ");
			mvprintw(22, col, "  ##  ##    ");
	                mvprintw(23, col, "      ##    ");
	                mvprintw(24, col, "      ##    ");
	                mvprintw(25, col, "      ##    ");
			mvprintw(26, col, "  ######### ");
			break;

		case 2:
			mvprintw(20, col, "   ######   ");
			mvprintw(21, col, "  ##    ##  ");
			mvprintw(22, col, "       ###  ");
			mvprintw(23, col, "      ###   ");
			mvprintw(24, col, "    ###     ");
			mvprintw(25, col, "  ###       ");
			mvprintw(26, col, " ########## ");
			break;

		case 3:
			mvprintw(20, col, "   ######   ");
			mvprintw(21, col, " ###    ### ");
			mvprintw(22, col, "        ### ");
			mvprintw(23, col, "     ####   ");
			mvprintw(24, col, "        ### ");
			mvprintw(25, col, " ###    ### ");
			mvprintw(26, col, "   ######   ");
			break;

		case 4:               
                        mvprintw(20, col, "     ####   ");
                        mvprintw(21, col, "    ## ##   ");
                        mvprintw(22, col, "   ##  ##   ");
                        mvprintw(23, col, "  ##   ##   ");
                        mvprintw(24, col, " ########## ");
                        mvprintw(25, col, "       ##   ");
                        mvprintw(26, col, "       ##   ");
			break;

		case 5:		
                        mvprintw(20, col, " ########## ");
                        mvprintw(21, col, " ##         ");
                        mvprintw(22, col, " ##         ");
                        mvprintw(23, col, " #########  ");
                        mvprintw(24, col, "         ## ");
                        mvprintw(25, col, "         ## ");
                        mvprintw(26, col, " #########  ");
			break;

                case 6:
                        mvprintw(20, col, "  ########  ");
                        mvprintw(21, col, " ##      ## ");
                        mvprintw(22, col, " ##         ");
                        mvprintw(23, col, " #########  ");
                        mvprintw(24, col, " ##      ## ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, "  ########  ");
			break;

                case 7:
                        mvprintw(20, col, " ########## ");
                        mvprintw(21, col, "        ##  ");
                        mvprintw(22, col, "       ##   ");
                        mvprintw(23, col, "      ##    ");
                        mvprintw(24, col, "     ##     ");
                        mvprintw(25, col, "    ##      ");
                        mvprintw(26, col, "   ##       ");
			break;

                case 8:
                        mvprintw(20, col, "  ########  ");
                        mvprintw(21, col, " ##      ## ");
                        mvprintw(22, col, " ##      ## ");
                        mvprintw(23, col, "  ########  ");
                        mvprintw(24, col, " ##      ## ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, "  ########  ");
			break;
                case 9:
                        mvprintw(20, col, "  #######  ");
                        mvprintw(21, col, " ##     ## ");
                        mvprintw(22, col, " ##     ## ");
                        mvprintw(23, col, "  #######  ");
                        mvprintw(24, col, "      ##   ");
                        mvprintw(25, col, "     ##    ");
                        mvprintw(26, col, "    ##     ");
			break;	
		}   	
}

void showCountDown(int time) {
	switch(time) {
		case 1:
                        mvprintw(18, 60, "      ###   ");
                        mvprintw(19, 60, "     ####   ");
                        mvprintw(20, 60, "   ##  ##   ");
                        mvprintw(21, 60, "       ##   ");
                        mvprintw(22, 60, "       ##   ");
                        mvprintw(23, 60, "       ##   ");
                        mvprintw(24, 60, "  ######### ");
                        break;

		case 2:
                        mvprintw(18, 60, "   ######   ");
                        mvprintw(19, 60, "  ##    ##  ");
                        mvprintw(20, 60, "       ###  ");
                        mvprintw(21, 60, "      ###   ");
                        mvprintw(22, 60, "    ###     ");
                        mvprintw(23, 60, "  ###       ");
                        mvprintw(24, 60, " ########## ");
                        break;

		case 3:			                       
		       	mvprintw(18, 60, "   ######   ");
                        mvprintw(19, 60, " ###    ### ");
                        mvprintw(20, 60, "        ### ");
                        mvprintw(21, 60, "     ####   ");
                        mvprintw(22, 60, "        ### ");
                        mvprintw(23, 60, " ###    ### ");
                        mvprintw(24, 60, "   ######   ");
			break;
	}
}

void setTimeOverGage(int currentTime) {
       	mvprintw(2, 12, "|                                                                                |");
	mvprintw(3, 12, "|                                                                                |");
	for(int i = 0; i < currentTime; i++) {
		mvprintw(2, 13 + i * 8, "########");
	}
}
