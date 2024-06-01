typedef struct {
    char username[50];
    int score;
} Player;

typedef struct {
	Player* members;
	int size;
} Players;

void showPlayingView();
void printHelp(char*);
void printRank(Players unit);
void showScore(int, int);
void enterMode(int);
void add(char*);
void showMainView();
void setSelectionCursor();
void printStairs(int*);
