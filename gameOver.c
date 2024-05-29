#include <curses.h>
#include<stdlib.h>
#include <stdio.h>

#define ENTER 10
#define BACKSPACE_KEY 127
#define BOX_HEIGHT 10
#define BOX_WIDTH 40

int isAlphabet(char key) {
    return ('A' <= key && key <= 'Z') || ('a' <= key && key <= 'z');
}
char changeUpperCase(char key) {
    if ('a' <= key && key <= 'z') {
        return 'A' + (key - 'a');
    }
}
char* inputUserName() {
    clear();
    initscr();             // curses 모드 시작
    cbreak();              // 라인 버퍼링을 비활성화하고, 즉시 입력을 읽을 수 있게 함
    noecho();              // 입력된 문자를 화면에 표시하지 않음
    curs_set(1);           // 커서를 보이게 설정
    // 입력된 문자열을 저장할 버퍼
    char* buffer = (char*)malloc(sizeof(char) * 4);
    int index = 0;

    // 창의 크기 얻기
    int height, width;
    getmaxyx(stdscr, height, width);

    // 박스의 크기 설정
    int start_y = (height - BOX_HEIGHT) / 2;
    int start_x = (width - BOX_WIDTH) / 2;

    // 박스 생성
    WINDOW* win = newwin(BOX_HEIGHT, BOX_WIDTH, start_y, start_x);
    box(win, 0, 0);
    mvwprintw(win, 1, 5, "Please Input Three Alphabet");
    mvwprintw(win, 2, 10, "Submission is Enter");
    mvwprintw(win, 5, 12, "INPUT : ");
    wrefresh(win);
    int ch;
    while (1) {
        // 입력된 문자를 버퍼에 추가
        if (((ch = wgetch(win))) == ENTER) {
            return buffer;
        }
            
        if ((ch == BACKSPACE_KEY)) {
            if (index > 0) {
                index--;
                buffer[index] = '\0';
            }
        }
        else if(index < 3 && isAlphabet(ch)) {
           // 입력된 문자를 버퍼에 추가
           buffer[index++] = changeUpperCase(ch);
           buffer[index] = '\0';

        }

        // 버퍼에 저장된 문자열을 화면에 출력
        mvwprintw(win, 5, 12, "INPUT : %s", buffer);
        wclrtoeol(win);  // 현재 라인에서 커서 이후의 모든 문자 지우기
        wrefresh(win);
    }
}

