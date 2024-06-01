#include<curses.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include "stairs.h"
#include "InfStair.h"
#include "outPutView.h"
#include "gameOver.h"

#define SUCESS 1
#define FAIL 0
#define GAME_OVER_TIME 10

int setTicker(int n_msecs);
void handleFailKey();
void tickEvent();
void CheckKeyDirection(int key);
void countDown();

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
	//this func handle GameOver case
	signal(SIGALRM, SIG_IGN);
	gameOver = 1;// gameOver
	char* userName = inputUserName();
	scoreInput(userName,score);
	free(userName);
	clearQueue();
	//*to do : invoke showGameOverView(score) in outputView.c and show GameOverView*
}
void tickEvent() {
	currentTime--;
	//*to do : invoke setTimeOverGage(currentTime) in outputView.c and show GameOverView
	showPlayingView();
	if (currentTime <= 0) {
		handleFailKey();
	}
}
void CheckKeyDirection(int key) {
	if (isCorrectDirection(key)) {
		//if isCorrectKey(key) is true in stairs.c
		printw("correct");
		refresh();
		score++;
		currentTime = GAME_OVER_TIME;
		//*to do : invoke showPlayingView() in outputView.c func print playing view
	}
	else {
		//if isCorrectKey(key) is false in stairs.c
		printw("unCorrect");
		refresh();
		handleFailKey();
	}
}
void countDown() {
	int time = 3;
	while (time--) {
		//*to do :invoke showCountDown(time) in outputView.c func print 3,2,1 count down view*
		printCountDown(time);
		sleep(1);
	}
}
void startGame(){
	void tickEvent();
	init();//invoke init() in stairs.c
	score = 0;
	gameOver = 0;
	currentTime = GAME_OVER_TIME;
	signal(SIGALRM, tickEvent);
	//three count down before game start
	countDown();

	//*todo : invoke showPlayingView() in outputView.c func print playing view
	showPlayingView();


	if (setTicker(1000) == -1) {
		perror("[InfStair] fail setTicker");
	}

	int key;
	while (!gameOver) {
		key = getch();
		if (key == KEY_LEFT || key == KEY_RIGHT) {
			CheckKeyDirection(key);
		}
	}

}


