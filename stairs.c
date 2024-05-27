#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<time.h>
#include "stairs.h"

typedef struct Stair{
	int dir;//stair direction
	struct Stair* next;
} Stair;
typedef struct{
	Stair* next;
	Stair* last;
}Header;
Header* head;

void push(Stair* stair) {

	if (head->next == NULL) {
		head->next = stair;
		head->last = stair;
	}
	else {
		Stair* lastStair = head->last;
		lastStair->next = stair;
		head->last = stair;
	}
}
Stair* createStair(){
	int randomDir = rand() % 2; // create Random Direction
	Stair* newStair = (Stair*)malloc(sizeof(Stair));
	newStair->dir = (randomDir == 0) ? KEY_LEFT : KEY_RIGHT; // 0 KEY_LEFT, 1 KEY_RIGHT
	return newStair;
}
void createNewStair() {
	//create stair and push queue
	push(createStair());
}
void init(){
	//create struct stair and push it
	srand(time(0));
	head = (Header*)malloc(sizeof(Header));
	head->next = NULL;
	head->next = NULL;

	//create 10 stair and push
	for (int i = 0; i < 10; i++) {
		push(createStair());
	}
}
Stair* poll(){
	// poll element and return stair
	if (head->next == NULL) {
		//if queue is empty, process exit
		perror("[stairs.c] stair queue is empty");
	}

	Stair* popStair = head->next;
	//if popStair is last element in queue, head->next and last set NULL
	if (popStair->next == NULL) {
		head->next = NULL;
		head->last = NULL;
	}
	else {
		head->next = popStair->next;
	}
	return popStair;
}
void clearQueue(){
	//clear queue
	Stair* nextTemp = head->next;
	Stair* freeTemp = head->next;
	while (freeTemp != NULL) {
		nextTemp = nextTemp->next;
		free(freeTemp);
		freeTemp = nextTemp;
	}
	free(head);
}
int isCorrectDirection(int key){
	//poll and compare direction
	Stair* stair = poll();
	return stair->dir == key;
}
int* getStairsDir(){
	int idx = 0;
	int* arr=(int*)malloc(sizeof(int));
	Stair* stair = head->next;
	while(stair != NULL){
		arr[idx++] = stair->dir;
		stair = stair->next;
	}	
	return arr;
}
