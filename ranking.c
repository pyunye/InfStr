#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "outPutView.h"
#include "ranking.h"
void rank(){
	Players* unit = scoreOutput();
	do{
		printRank(unit);
	} while (getch() != 'b');
}



