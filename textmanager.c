#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "textmanager.h"

int compare(const void *a, const void *b) {
    return ((Player *)b)->score - ((Player *)a)->score;
}

void scoreInput(char *username, int score) {
    FILE *f;
    if ((f = fopen("score.txt", "a")) == NULL) {
        fprintf(stderr, "file write\n");
        exit(1);
    }
    fprintf(f, "%s %d\n", username, score);
    fclose(f);
}

Players* scoreOutput() {
    FILE *f;
    int num_players = 0;
    Player *players = malloc(MAX_SIZE * sizeof(Player)); 
    Players* unit = malloc(MAX_SIZE * sizeof(Players));
    unit->members = players;

    // 파일 열기
    if ((f = fopen("score.txt", "r")) == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        exit(1);
    }

    // 파일에서 데이터 읽기
    while (fscanf(f, "%s %d", players[num_players].username, &players[num_players].score) != EOF) {
        (num_players)++;
    }
    unit->size = num_players;
    // 소팅
    qsort(unit->members, unit->size, sizeof(Player), compare);
    
    fclose(f); // 파일 닫기
    


    return unit;
}
