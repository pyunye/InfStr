#include <stdio.h>
#include <stdlib.h>
#include "textmanager.h"
#include <curses.h>

void rank(){
	Player *players = scoreOutput();
	while(getKey() != 'b'){
		printRank(players);
	}
}



