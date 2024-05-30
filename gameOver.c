#include <curses.h>
#include <stdlib.h>
#include "gameOver.h"

#define ENTER 10
#define BACKSPACE_KEY 127

int isAlphabet(char key);
char changeUpperCase(char key);

int isAlphabet(char key) {
    return ('A' <= key && key <= 'Z') || ('a' <= key && key <= 'z');
}
char changeUpperCase(char key) {
    if ('a' <= key && key <= 'z') {
        return 'A' + (key - 'a');
    }
    return key;
}
char* inputUserName() {
    clear();
    cbreak();              // 라인 버퍼링을 비활성화하고, 즉시 입력을 읽을 수 있게 함
    curs_set(1);           // 커서를 보이게 설정

    // 입력된 문자열을 저장할 버퍼
    char* buffer = (char*)malloc(sizeof(char)*5);
    int index = 0;

    // 창의 크기 얻기
    int height, width;
    getmaxyx(stdscr, height, width);

    // 박스의 크기 설정
    int box_height = 10;
    int box_width = 40;
    int start_y = (height - box_height) / 2;
    int start_x = (width - box_width) / 2;

    mvprintw(start_y - 2, start_x + (box_width - 9) / 2, "Game Over");
    refresh();

    // 박스 생성
    WINDOW* win = newwin(box_height, box_width, start_y, start_x);
    box(win, 0, 0);
    mvwprintw(win, 1, 5, "Please Input Three Alphabet");
    mvwprintw(win, 2, 10, "Submission is Enter");
    mvwprintw(win, 5, 12, "INPUT : ");
    wrefresh(win);

    int ch;
    while (1) {
        // 입력된 문자를 버퍼에 추가
        ch = wgetch(win);

        // ENTER 키 처리
        if (ch == ENTER) return buffer;

        // 백스페이스 키 처리
        if (ch == BACKSPACE_KEY) {
            if (index > 0) {
                index--;
                buffer[index] = '\0';
            }
        }
        // 알파벳 문자를 처리
        else if (isAlphabet(ch)) {
            if (index < 3) {
                buffer[index++] = changeUpperCase(ch);
                buffer[index] = '\0';
            }
        }

        // 버퍼에 저장된 문자열을 화면에 출력
        mvwprintw(win, 5, 12, "INPUT : %s", buffer);
        wclrtoeol(win);  // 현재 라인에서 커서 이후의 모든 문자 지우기
        wrefresh(win);
    }
}

