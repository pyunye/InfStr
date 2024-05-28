#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>
#define BACKKEY "> back key 'b'\n\n"
typedef struct {
    char username[50];
    int score;
} Player;

typedef struct {
	Player* members;
	int size;
} Players;

void printHelp(char []);
void help(){
	char helpText[512] = "<<<<<	Help : Infinite Stair	   >>>>>\n\n* Press left or right to move upstair!\n* If you don’t press any button for a long time or press a wrong button, game is over.\n* If you get a coin, you can press the button slowly.\n\n";
	while(getch() != 'b'){
		printHelp(helpText);
	}
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
int main(){
	help();
	Player players[10];
	Players unit;
	unit.members = players;
	unit.members[0].score = 10;
	unit.size = 1;
	strcpy(unit.members[0].username, "ABC");
	printRank(unit);
}

