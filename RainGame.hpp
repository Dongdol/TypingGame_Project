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
using namespace std;

#define STAGE1_WORD_DOWN_TIME 5
#define WORD_MAX 50
#define START_MODE 0
#define STAGE1_MODE 1
#define STAGE2_MODE 2
#define STAGE3_MODE 3
#define BOSS_MODE 4
#define STAGE1_SCORE 10
#define STAGE2_SCORE 20
#define STAGE3_SCORE 30
#define   BOSS_SCORE 50
 
//Fruit
static char* STAGE1[] = {"Banana","Mango","Apple","Watermelon","Orange","Strawberry","Durian","Grape","Citrus","Mangosteen","Plum","Peach","Pineapple","Coconnut","Sugarcane","Blueberry","Pear","flg","Persimmon","Pomegranate"};
//Music
static char* STAGE2[] = {"You And I", "Reality", "Workerholic", "Blueming", "Mirotic","Yes or Yes", "Heartshaker", "IDOL","Travel","Good Day","Attention","All falls down","Despacito","Shape of you","DINOSAUR","UmpahUmpah"
 ,"Viva La Vida","What the hell","Alone","2002","Lost Stars","Love$ick","7rings","Speechless","Handclap","We all lie","The Ocean","Move Like Jagger","Reminiscence","HymnForTheWeekend" };
//Discipline
static char* STAGE3[] = {"Mathemtics","Physics", "Quantum Mechanics","Apparel study","Religious studies","Food and Nutrition",
"Quantum Physics","Linguistics","Material engineering", "Chemistry", "Science of law", "Computer Science","Philosophy","Economics","Urban engineering"
,"literature","Psychology","Korean Medicine","Earth science","Pedagogy Education","Astronomy","Medicine","Architecture","Biology","Archaeology",
"Mechanical engineering","Dentistry","Sociology","Humanities","Natural science"};

static char* BOSS[] ={"Infix to Postfix", "1 4+ 5 4 + + 2 /", "pthread_exit()","depth_first_search","Message Queue",
"iterator begin()", "void signalHandler()","Semaphore","Symbolic Link","std::stack<int>","int mkfifo()","sigpromask()",
"DIR* opendir()"};
static int SCORE_TYPE=STAGE1_SCORE;
static int MODE=START_MODE;
static int score=0;
static int hp=5;
static char stageName[10];
static int BOSS_HP=3;
static char BOSS_HP_BAR[10];
static int enter_num;
static char hp_Bar[10];
static char score_Bar[10];
static char enter_Bar[20] = "	| Enter | : ";
static int input;
static pthread_mutex_t lock;

typedef struct WordNode* WordNodePointer;
typedef struct WordNode
{
    int row, col;
    char str[WORD_MAX];
    WordNodePointer up, down;

}WordNode;

    


class Rain
{
    private:


    public:
      void GameComplete();
      void StageChange();
      void Print_UI();
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
      void GameOver();
      char *Return_Str();
      char enter[30] = {0};

};
typedef void *(*THREADFUNCPTR)(void *);



char* Return_Str();
void Blank_OutputWord();
void Blank_OutputWord_All();





#endif
