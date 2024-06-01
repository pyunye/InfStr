#define MAX_SIZE 100
typedef struct {
    char username[50];
    int score;
} Player;

typedef struct {
	Player* members;
	int size;
} Players;

int compare(const void* , const void*);
void scoreInput(char*, int);
Player *scoreOutput();

