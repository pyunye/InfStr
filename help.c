#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void help(){
	char helpText[512] = "<<<<<	Help : Infinite Stair	   >>>>>\n\n* Press left or right to move upstair!\n* If you don’t press any button for a long time or press a wrong button, game is over.\n* If you get a coin, you can press the button slowly.\n\n";
	while(getKey() != 'b'){
		printHelp(helpText);
	}
}

