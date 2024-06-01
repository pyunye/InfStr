#include <stdio.h>
#include <stdlib.h>
#include "textmanager.h"
#include <curses.h>
#include "outputView.h"
void rank(){
	Players unit = scoreOutput();
	while(getch() != 'b'){
		printRank(unit);
	}
}



