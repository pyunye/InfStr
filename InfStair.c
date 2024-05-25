#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<unistd.h>
#include<signal.h>

int score;
int CheckKeyDirection(int key) {
	//success return 1, fail 0

	if () {
		//if isCorrectKey(key) is true in stairs.c
		//flus score
		//alarm(time) reset
		//invoke SuccessKeyHandler
	}
	else {
		//if isCorrectKey(key) is false in stairs.c
		// alarm(0) init
		//invoke FailKeyHandler
		exit(0);
	}
}
void countDown() {
	int time = 3;
	while (time--) {
		//invoke showCountDown(time) in outputView.c func print 3,2,1 count down view
		sleep(1);
	}
}
void startGame(){
	//invoke init() in stairs.c	
	//signal(SIG_ARLM,hadleFailKey func in FailKeyHandler.c)
	//init alarm()
	
	//three count down before game start
	countDown();

	//invoke showPlayingView() in outputView.c func print playing view
	
	while (1) {
		int key = getch();
		if (key == KEY_LEFT || KEY_RIGHT) {
		CheckKeyDirection(key);
		}
	}
	
}

