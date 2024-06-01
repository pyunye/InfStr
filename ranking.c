#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "outPutView.h"
void rank(){
	Players unit = scoreOutput();
	while(getch() != 'b'){
		printRank(unit);
	}
}



