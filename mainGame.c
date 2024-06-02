#include<stdlib.h>
#include<curses.h>
#include<unistd.h>
#include "InfStair.h"
#include "outPutView.h"
#include "help.h"
#include "ranking.h"

#define ENTER 10
#define START 0
#define HELP 1
#define RANKING 2
#define QUIT 3

void enterMode(int select){
	switch (select) {
		case START: //invoke startGame() in InfStair.c
			startGame();
			break;
		case HELP:
			help();
			break;
		case RANKING:
			rank();
			break;
		case QUIT: //game quit
			endwin();
			exit(0);
			break;
	}
}
int main(){
	initscr();
	crmode();
	keypad(stdscr, TRUE); //for arrow,enter key
	noecho();
	clear();
	curs_set(0);

	showMainView();
	
	int key;
	int select = 0;
	while (1) {
		key = getch();
		switch (key) {
		case KEY_UP:
			select = (select - 1 + 4) % 4;
			setSelectionCursor(select);
			break;
		case KEY_DOWN:
			select = (select + 1) % 4;
			setSelectionCursor(select);
			break;
		case ENTER:
			enterMode(select);
			showMainView();
			select = 0;
			break;
		}
	}
}
