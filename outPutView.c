#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "outPutView.h"
#include "stairs.h"

#define BLANK " "
#define ARROW ">"
#define STAIR "[###]"
#define ENTER 10
#define BACKKEY "> back key 'b'\n\n"
#define NEXTSTEP "<< press 'b' >>"

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
	
    	mvprintw(7, 35, " _____  _   _ ______  _____  _   _  _____  _____  _____     ");
    	mvprintw(8, 35, "|_   _|| \\ | ||  ___||_   _|| \\ | ||_   _||_   _||  ___| ");
    	mvprintw(9, 35, "  | |  |  \\| || |_     | |  |  \\| |  | |    | |  | |__   ");
    	mvprintw(10, 35, "  | |  | . ` ||  _|    | |  | . ` |  | |    | |  |  __|    ");
    	mvprintw(11, 35, " _| |_ | |\\  || |     _| |_ | |\\  | _| |_   | |  | |___  ");
    	mvprintw(12, 35, " \\___/ \\_| \\_/\\_|     \\___/ \\_| \\_/ \\___/   \\_/  \\____/  ");
    	mvprintw(15, 40, "   _____  _____   ___   _____ ______  _____                   ");
    	mvprintw(16, 40, "  /  ___||_   _| / _ \\ |_   _|| ___ \\/  ___|                ");
    	mvprintw(17, 40, "  \\ `--.   | |  / /_\\ \\  | |  | |_/ /\\ `--.               ");
    	mvprintw(18, 40, "   `--. \\  | |  |  _  |  | |  |    /  `--. \\                ");
    	mvprintw(19, 40, "  /\\__/ /  | |  | | | | _| |_ | |\\ \\ /\\__/ /              ");
    	mvprintw(20, 40, "  \\____/   \\_/  \\_| |_/ \\___/ \\_| \\_|\\____/            ");
    	mvprintw(25, 57, ">  START");
    	mvprintw(26, 60, "HELP");
    	mvprintw(27, 60, "RANKING");
    	mvprintw(28, 60, "QUIT");
	
	setSelectionCursor(0);
	refresh();
}
void setSelectionCursor(int select) {
	
	static int old_select = 0;

	switch (old_select) {
		case 0:
			move(25, 57);
			break;
		case 1:
			move(26, 57);
			break;
		case 2:
			move(27, 57);
			break;
		case 3:
			move(28, 57);
			break;

	}
	addstr(BLANK);

	old_select = select;
	switch (select) {
		case 0:
			move(25, 57);
			break;
		case 1:
			move(26, 57);
			break;
		case 2:
			move(27, 57);
			break;
		case 3:
			move(28, 57);
			break;
	}
	addstr(ARROW);
	refresh();
}
void printHelp(char text[]){
	clear();

	addstr(text);
	addstr(BACKKEY);
	refresh();
}
void printRank(Players* unit){
	clear();
	int i=0;
	while(i < unit->size && i < 10){
		printw(" Rank %d : %d(%s)\n", i + 1, unit->members[i].score, unit->members[i].username);
		i++;
	}
	addstr(BACKKEY);
	refresh();
}
void showPlayingView(int score) {
	clear();
	move(6, 65);
	printStairs(getStairsDir());
	mvprintw(4, 55, "score : %d",score);
	refresh();
}
void setTimeOverGage(int currentTime) {
	mvprintw(5, 30, "|                                                                        |");
	mvprintw(6, 30, "|                                                                        |");
	for (int i = 1; i < currentTime; i++) {
		mvprintw(5, 23 + 8 * i, "########");
		mvprintw(6, 23 + 8 * i, "########");
	}
	refresh();
}
void printStairs(int stairs[]) {
	int player_col= 60;
	int player_row = 30;

	int move_row = 2;
	int move_col = 5;
	int stair_row = player_row;
	int stair_col = player_col;

	move(player_row - 1, player_col + 1);
	addstr("*");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		move(stair_row, stair_col);
		addstr(STAIR);
		stair_row -= move_row;
		stair_col += (stairs[i] == KEY_LEFT) ? -move_col : move_col;
	}
}
void printCountDown(int time) {
	clear();
	switch (time) {
		case 0:
			mvprintw(20, 60, "     ###    ");
			mvprintw(21, 60, "    ####    ");
			mvprintw(22, 60, "  ##  ##    ");
			mvprintw(23, 60, "      ##    ");
			mvprintw(24, 60, "      ##    ");
			mvprintw(25, 60, "      ##    ");
			mvprintw(26, 60, "  ######### ");
			break;

		case 1:
			mvprintw(20, 60, "   ######   ");
			mvprintw(21, 60, "  ##    ##  ");
			mvprintw(22, 60, "       ###  ");
			mvprintw(23, 60, "      ###   ");
			mvprintw(24, 60, "    ###     ");
			mvprintw(25, 60, "  ###       ");
			mvprintw(26, 60, " ########## ");
			break;

		case 2:
			mvprintw(20, 60, "   ######   ");
			mvprintw(21, 60, " ###    ### ");
			mvprintw(22, 60, "        ### ");
			mvprintw(23, 60, "     ####   ");
			mvprintw(24, 60, "        ### ");
			mvprintw(25, 60, " ###    ### ");
			mvprintw(26, 60, "   ######   ");
			break;
	}
	refresh();
}
void showGameOverView(int score) {
	clear();
	move(7, 0);
	prt_row = 7;

	add("         ######      ####    ##       ## ########              #####    ##       ##  #######  #######        ###       "); 
    add("       ##     ##    ##  ##   ###    #### ##                  ###   ###  ##       ##  ##       ##    ##       ###       ");
	add("      ##           ##    ##  ## ## ## ## ##                 ##       ## ##       ##  ##       ##    ##       ###       ");
        add("      ##    ##### ########## ##  ###  ## ########           ##       ##  ##     ##   #######  #######        ###       ");
        add("      ##      ##  ##      ## ##       ## ##                 ##       ##   ##   ##    ##       ##    ##       ###       ");
        add("       ##     ##  ##      ## ##       ## ##                  ###   ###     ## ##     ##       ##     ##                ");
        add("        #######   ##      ## ##       ## ########              #####        ###      #######  ##      ##     ###       ");
                     
	prt_row = 21;
	move(21, 0);

	add("         ######    ######     #####     ######     ########            ");
        add("        ##    ##  ##        ###   ###   ##    ##   ##                  ");
        add("        ##       ##        ##       ##  ##    ##   ##            ##    ");
        add("         #####   ##        ##       ##  ######     ########            ");
        add("              ## ##        ##       ##  ##    ##   ##            ##    ");
        add("        ##    ##  ##        ###   ###   ##     ##  ##                  ");
        add("         ######    ######     #####     ##      ## ########            ");

	int score_len = 0;
	int score_num = score;	
	int score_col = 12;
	if(score == 0)
		showScore(0, 70);
	else{
		while (score_num != 0) {
			score_len++;
			score_num /= 10;
		}
		for(int i = score_len - 1; i >= 0; i--) {
			showScore(score % 10, 70 +  i * score_col); 
			score /= 10;
		}	
	}
	mvprintw(30, 50, NEXTSTEP);
	refresh();
}
void showScore(int score, int col) {

	switch(score) {
		case 0:
			mvprintw(21, col, "    ####    ");
			mvprintw(22, col, "  ##    ##  ");
			mvprintw(23, col, " ##      ## ");
			mvprintw(24, col, " ##      ## ");
			mvprintw(25, col, " ##      ## ");
			mvprintw(26, col, "  ##    ##  ");
			mvprintw(27, col, "    ####    ");
			break;						 
			
		case 1:
			mvprintw(21, col, "     ###    ");
                        mvprintw(22, col, "    ####    ");
			mvprintw(23, col, "  ##  ##    ");
	                mvprintw(24, col, "      ##    ");
	                mvprintw(25, col, "      ##    ");
	                mvprintw(26, col, "      ##    ");
			mvprintw(27, col, "  ######### ");
			break;

		case 2:
			mvprintw(21, col, "   ######   ");
			mvprintw(22, col, "  ##    ##  ");
			mvprintw(23, col, "       ###  ");
			mvprintw(24, col, "      ###   ");
			mvprintw(25, col, "    ###     ");
			mvprintw(26, col, "  ###       ");
			mvprintw(27, col, " ########## ");
			break;

		case 3:
			mvprintw(21, col, "   ######   ");
			mvprintw(22, col, " ###    ### ");
			mvprintw(23, col, "        ### ");
			mvprintw(24, col, "     ####   ");
			mvprintw(25, col, "        ### ");
			mvprintw(26, col, " ###    ### ");
			mvprintw(27, col, "   ######   ");
			break;

		case 4:               
                        mvprintw(21, col, "     ####   ");
                        mvprintw(22, col, "    ## ##   ");
                        mvprintw(23, col, "   ##  ##   ");
                        mvprintw(24, col, "  ##   ##   ");
                        mvprintw(25, col, " ########## ");
                        mvprintw(26, col, "       ##   ");
                        mvprintw(27, col, "       ##   ");
			break;

		case 5:		
                        mvprintw(21, col, " ########## ");
                        mvprintw(22, col, " ##         ");
                        mvprintw(23, col, " ##         ");
                        mvprintw(24, col, " #########  ");
                        mvprintw(25, col, "         ## ");
                        mvprintw(26, col, "         ## ");
                        mvprintw(27, col, " #########  ");
			break;

                case 6:
                        mvprintw(21, col, "  ########  ");
                        mvprintw(22, col, " ##      ## ");
                        mvprintw(23, col, " ##         ");
                        mvprintw(24, col, " #########  ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, " ##      ## ");
                        mvprintw(27, col, "  ########  ");
			break;

                case 7:
                        mvprintw(21, col, " ########## ");
                        mvprintw(22, col, "        ##  ");
                        mvprintw(23, col, "       ##   ");
                        mvprintw(24, col, "      ##    ");
                        mvprintw(25, col, "     ##     ");
                        mvprintw(26, col, "    ##      ");
                        mvprintw(27, col, "   ##       ");
			break;

                case 8:
                        mvprintw(21, col, "  ########  ");
                        mvprintw(22, col, " ##      ## ");
                        mvprintw(23, col, " ##      ## ");
                        mvprintw(24, col, "  ########  ");
                        mvprintw(25, col, " ##      ## ");
                        mvprintw(26, col, " ##      ## ");
                        mvprintw(27, col, "  ########  ");
			break;
                case 9:
                        mvprintw(21, col, "  #######  ");
                        mvprintw(22, col, " ##     ## ");
                        mvprintw(23, col, " ##     ## ");
                        mvprintw(24, col, "  #######  ");
                        mvprintw(25, col, "      ##   ");
                        mvprintw(26, col, "     ##    ");
                        mvprintw(27, col, "    ##     ");
			break;	
		}   	
}
