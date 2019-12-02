#ifndef __TEST_H__
#define __TEST_H__
#define WORD_MAX 50
#include <curses.h>
#include <iostream>
#include <list>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

typedef struct WordNode* WordNodePointer;
typedef struct WordNode
{
    int row, col;
    char str[WORD_MAX];
    WordNodePointer up, down;

}WordNode;

class Rain {
  private:

    char enter[30] = {0};
    int enter_num;
    int hp = 10;
    char hp_Bar[10];
    char score_Bar[10];
    char enter_Bar[20] = "	| Enter | : ";
    char stage[10] = "STAGE";
    char stageName[15] = "숲";
    int score = 0;
    int input;

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  public:

    void FindWords(char *str);
    void *Game_Board_1(void *);
    void *Game_Board_2(void *);
    void *Game_Board_3(void *);
    void Game_Start();
    void Draw(int row, int col, char *str);
    void Print_Words();
    char **Get_Words();
    void Down_Words();
    WordNodePointer Initnode(void);
    WordNodePointer CreateWord(const char *str);
    void CreateList_1();
    void CreateList_2();
    void CreateList_3();
    void GameOver();
    void GameComplete();
    const char *Return_STAGE1();
    const char *Return_STAGE2();
    const char *Return_STAGE3();

    // Fruit
    const char *STAGE1[20] = {"Banana",    "Mango",      "Apple",     "Watermelon",
                      "Orange",    "Strawberry", "Durian",    "Grape",
                      "Citrus",    "Mangosteen", "Plum",      "Peach",
                      "Pineapple", "Coconnut",   "Sugarcane", "Blueberry",
                      "Pear",      "flg",        "Persimmon", "Pomegranate"};
    // Music
    const char *STAGE2[30] = {
        "You And I",    "Reality",          "Workerholic", "Blueming",
        "Mirotic",      "Yes or Yes",       "Heartshaker", "IDOL",
        "Travel",       "Good Day",         "Attention",   "All falls down",
        "Despacito",    "Shape of you",     "DINOSAUR",    "UmpahUmpah",
        "Viva La Vida", "What the hell",    "Alone",       "2002",
        "Lost Stars",   "Love$ick",         "7rings",      "Speechless",
        "Handclap",     "We all lie",       "The Ocean",   "Move Like Jagger",
        "Reminiscence", "HymnForTheWeekend"};
    // Disciplines
    const char *STAGE3[30] = {"Mathemtics",
                      "Physics",
                      "Quantum Mechanics",
                      "Apparel study",
                      "Religious studies",
                      "Food and Nutrition",
                      "Quantum Physics",
                      "Linguistics",
                      "Material engineering",
                      "Chemistry",
                      "Science of law",
                      "Computer Science",
                      "Philosophy",
                      "Economics",
                      "Urban engineering",
                      "literature",
                      "Psychology",
                      "Korean Medicine",
                      "Earth science",
                      "Pedagogy Education",
                      "Astronomy",
                      "Medicine",
                      "Architecture",
                      "Biology",
                      "Archaeology",
                      "Mechanical engineering",
                      "Dentistry",
                      "Sociology",
                      "Humanities",
                      "Natural science"};
};
typedef void *(*THREADFUNCPTR)(void *);



void Blank_OutputWord();


#endif
