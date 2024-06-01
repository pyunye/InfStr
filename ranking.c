#include <stdio.h>
#include <stdlib.h>
#include "textmanager.h"
#include <curses.h>

void rank(){
	Players unit = scoreOutput();
	while(getKey() != 'b'){
		printRank(unit);
	}
}



