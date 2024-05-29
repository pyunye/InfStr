typedef struct Stair{
	int dir;
	struct Stair* next;
} Stair;
typedef struct{
	Stair* next;
	Stair* last;
} Header;
void createNewStair();
void init();
void clearQueue();
int isCorrectDirection(int key);
int* getStairsDir();
