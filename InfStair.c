#include<curses.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include "stairs.h"
#include "InfStair.h"
#include "outPutView.h"
#include "gameOver.h"

#define ENTER 10
#define SUCCESS 1
#define FAIL 0
#define GAME_OVER_TIME 10
#define INIT_TICKTIME 1000
#define TICK_TIME_BOUND 50

int setTicker(int n_msecs);
void handleFailKey();
void tickEvent();
void CheckKeyDirection(int key);
void countDown();
int getkeyboard();

int score;
int gameOver;
int currentTime;

int setTicker(int n_msecs) {
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
void handleFailKey() {
	//this func handles GameOver case
	signal(SIGALRM, SIG_IGN);
	gameOver = 1;// gameOver
	showGameOverView(score);
	char* userName = inputUserName();
	clear();
	scoreInput(userName,score);
	free(userName);
	clearQueue();
	
}
void tickEvent() {
	setTimeOverGage(currentTime);
	currentTime--;
	if (currentTime <= 0) {
		handleFailKey();
	}
}
void changeGameDifficult() {
	int changeTickTime = INIT_TICKTIME - (score / 10) * 15;
	changeTickTime = changeTickTime < TICK_TIME_BOUND ? TICK_TIME_BOUND : changeTickTime;
	setTicker(changeTickTime);
}
void handleSuccessKey() {
	score++;
	currentTime = GAME_OVER_TIME;
	createNewStair();
	showPlayingView(score);
	setTimeOverGage(currentTime);
	changeGameDifficult();
}
void CheckKeyDirection(int key) {
	if (isCorrectDirection(key)) {
		//if plyer input correct direction key, isCorrectKey(key) is true in stairs.c
		handleSuccessKey();
	}
	else {
		//if plyer input wrong direction key, isCorrectKey(key) is false in stairs.c
		handleFailKey();
	}
}
void countDown() {
	int time = 3;
	while (time--) {
		printCountDown(time);
		sleep(1);
	}

}
void initVariable() {
	score = 0;
	gameOver = 0;
	currentTime = GAME_OVER_TIME;
}
void startGame(){
	void tickEvent();
	init();//invoke init() in stairs.c
	initVariable();
	signal(SIGALRM, tickEvent);

    //three count down before game start
    countDown();
    showPlayingView(score);
    setTimeOverGage(currentTime);

    if (setTicker(INIT_TICKTIME) == -1) {
        perror("[InfStair] fail setTicker");
    }

    int key;
    while (!gameOver) {
        key = getkeyboard();
        if (key == KEY_LEFT || key == KEY_RIGHT) {
            CheckKeyDirection(key);
        }
    }
}

int getkeyboard(){
	timeout(0);
	int key = getch();
	timeout(-1);
	return key;
}


