#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>

#define ENTER 10
#define START 0
#define HELP 1
#define QUIT 2

void enterMode(int select){
	switch (select) {
		case START: //invoke startGame() in InfStair.c
			break; 
		case HELP: //invoke help() in help.c
			break;
		case QUIT: //game quit
			exit(0);
			break;
	}
}

int main(){
	initscr();
	crmode();
	keypad(stdscr, TRUE); // for arrow, enter key
	noecho();
	clear();
	curs_set(0);

	// invoke showMainView() in outPutView.c method print MainView with title and three option(start, help, quit);
	
	int key;
	int select = 0;
	while(1){
		key = getch();

		switch(key){
			case KEY_UP: // up Arrow Key
				select = (select - 1) < 0 ? 2 : 0 ; // three option with start, help, quit
				// show moving up select cusor
				addstr("up Arrow Key");
				break;
			case KEY_DOWN: // up Arrow Key
                select = (select + 1) % 3; // three option with start, help, quit
			// show moving down select cusor
				addstr("down Arrow Key");
                break;
			case ENTER: // enter key
				enterMode(select); // enter the mode of start or help or quit 
				addstr("  enter key  ");
				break;
		}
	}
		
}
