#include "rain.h"
#include <curses.h> // curses.h 사용하기 위해 링크 옵션으로 -lncurses 붙이기
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h> //스레드 사용
#include <unistd.h>
using namespace std;

//화면해상도 94*30 기준
//test
int score = 0;
char score_str[100] = "";
int hp = 5;
char hp_str[2] = "";
Node *fnode = 0;

Node* createNode() {
    Node *node;
    node = (Node *)malloc(sizeof(*node));
    node->nextNode = 0;
    return node;
}

void game() {

    pthread_t t1 = 0;

    initscr();
    clear();

    // score print
    move(1, 1);
    addstr("score : ");
    sprintf(score_str, "%d", score);
    addstr(score_str);
    refresh();

    // hp print
    move(1, 3);
    addstr("life  : ");
    sprintf(hp_str, "%d", hp);
    addstr(hp_str);
    refresh();

    //enter setting
    draw(16, 0, "==============================================================================================");
    draw(17, 0, "|   Enter   | :                                                                               ");
    draw(18, 0, "==============================================================================================");

    pthread_create(&t1, NULL, thread_word, NULL); // 스레드 생성

    pthread_join(t1, NULL);

    clear();
}

void * thread_word(void *none) {
    while(hp > 0){
        Node *dnode = 0; //drawing node = dnode

        addWord(randomWord(), (rand() % 40) + 8);
        dnode = fnode;

        while(dnode){
            draw(dnode->row, dnode->col, dnode->word);
            dnode = dnode->nextNode;
        }

        move(17, 12);

        sleep(1);
    }
}

//큐에 단어 추가
void addWord(const char * word,int col){
    Node *node1;
    Node *node2;

    if(fnode == 0){ //first node = fnode
        fnode = createNode();
        strcpy(fnode->word, word);
        fnode->row = 1;
        fnode->col = col;
    }
}
//단어 랜덤 반환
const char * randomWord(){
    const char *word[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                    "J", "K", "L", "M", "N", "P", "Q", "R", "S",
                    "T", "U", "V", "W", "X", "Y", "Z"};
    return word[rand() % 25];
}

//지정 위치 출력 함수
void draw(int row, int col, const char *str) {

    move(row, 0);
    addstr("								       "
           " 	");
    move(row, col);
    addstr(str);
    refresh();
}
