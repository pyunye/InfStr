#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "outPutView.h"
#include <curses.h>
void help(){
	char helpText[512] = "<<<<<     Help : Infinite Stair     >>>>>\n\n\n\n\n                    * Press left or right to move upstair!\n\n\n                    * If you don\'t press any button for a long time or press a wrong button, game is over.\n\n\n                    * If you get a coin, you can press the button slowly.\n\n";
	do{
		printHelp(helpText);
	} while (getch() != 'b');
}

