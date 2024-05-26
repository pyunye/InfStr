#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>

void help(){
	char helpText[512] = "<<<<<	Help : Infinite Stair	   >>>>>\n\n* Press left or right to move upstair!\n* If you don’t press any button for a long time or press a wrong button, game is over.\n* If you get a coin, you can press the button slowly.\n\n> Back key 'b'\n";
	while(getKey() != 'b'){
		printHelp(helpText);
	}
}
