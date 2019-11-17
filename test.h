#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <curses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#define STAGE1_WORD_DOWN_TIME 5
#define WORD_MAX 50
using namespace std;

typedef struct WordNode* WordNodePointer;
typedef struct WordNode
{
    int row, col;
    char str[WORD_MAX];
    WordNodePointer up, down;

}WordNode;

WordNodePointer ptr;
list<WordNodePointer> WordList;
list<WordNodePointer>::iterator Iter;


class Rain
{
    private:
      char enter[30] = {0};
      int enter_num;
      int score = 0;
      int hp = 20;
      char hp_Bar[10];
      char score_Bar[10];
      char enter_Bar[20] = "	| Enter | : ";
      char stage[10] = "STAGE";
      char stageName[15] = "숲";

    public:
      void FindWords(char* str);
      void *Game_Board(void *);
      void Game_Start();
      void Draw(int row, int col, char *str);
      void Print_Words();
      char **Get_Words();
      void Down_Words();
      WordNodePointer Initnode(void);
      WordNodePointer CreateWord(char *str);
      void CreateList();


};
typedef void *(*THREADFUNCPTR)(void *);

char* Return_Str();
void Blank_OutputWord();

 char* STAGE1[] = {"You And I", "Reality", "Workerholic", "HymnForTheWeekends", "Mirotic","Yes or Yes", "Heartshaker", "IDOL","Travel","Good Day","Attention","All falls down" };

 pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#endif
