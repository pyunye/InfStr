#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char username[50];
    int score;
} Player;

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

void scoreOutput() {
	 FILE *f;
    Player players[MAX_SIZE];
    int num_players = 0;

    // 파일 열기
    if ((f = fopen("score.txt", "r")) == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        exit(1);
    }

    // 파일에서 데이터 읽기
    while (fscanf(f, "%s %d", players[num_players].username, &players[num_players].score) != EOF) {
        num_players++;
    }

    // 소팅
    qsort(players, num_players, sizeof(Player), compare);

    // 소팅된 데이터 출력
    printf("Ranking:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%s - %d\n", players[i].username, players[i].score);
    }

    fclose(f); // 파일 닫기
}

int main() {
    char username[50];
    int score;
    
    printf("유저 이름을 입력하세요: ");
    scanf("%s", username);
    printf("점수를 입력하세요: ");
    scanf("%d", &score);
    
    scoreInput(username, score);
    scoreOutput();
    
    return 0;
}
