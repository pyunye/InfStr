#include <stdio.h>
#include <stdlib.h>
#include "textmanager.h"

int main(){
	Player *players = scoreOutput();
	printf("		Ranking\n");
	int i = 0;
	while(players[i].username[0] != '\0'){
		printf("%s : %d\n", players[i].username, players[i].score);
		i++;
	}
}



