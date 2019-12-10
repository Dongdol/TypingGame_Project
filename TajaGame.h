#ifndef _GAME_H_
#define _GAME_H_

#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <list>
#include <termios.h>
#include <stdio.h>


using namespace std;

#define SIZE_READ_TEXT_ENG 70 + 3
#define SIZE_READ_TEXT_HNG 101

#define SELECT_ENGLISH 1
#define SELECT_HANGUL 2

#define SCOREFILE "./userscore.dat"     // added

class Game {

  private:
    int select =0;
    char pathName[20] ={'\0',};
    char put_String_E[SIZE_READ_TEXT_ENG] = {'\0',  };
    char Buf_E[SIZE_READ_TEXT_ENG] = { '\0',};
    char err_Type_E[SIZE_READ_TEXT_ENG] = { '\0', };
    char put_String_H[SIZE_READ_TEXT_HNG] = {'\0',};
    char Buf_H[SIZE_READ_TEXT_HNG] = {'\0',};
    char err_Type_H[SIZE_READ_TEXT_HNG]={'\0',};
    int total_typenum = 0; //타이핑되는 총 글자수 입력 (공백 포함)
    int err_typenum = 0;
    float accuarcy = 0.0;
    int type_start_Time;
    int type_during_Time;
    list<string> English={"명언","명언2","명언3"};
    list<string> Hangul={"이별택시","자화상"};
    list<string> Text_Mode;
    list<string>::iterator iter;
    char curText[10];
    char userName[10];

  public:
    int basicgame();
    int Return_ErrTypeNum(char Buf[], char put_String[], int str_Size);
    void Remove_Enter(char put_String[], int len);
    void Print_Result();
    char* Print_TextList(int select);
    
};

// added part started

static int fd;
static int w_Size;
static int r_Size;

typedef struct UserScore {
        char name[10];
        double spd;
        double accuracy;
        char text[10];
} UserScore;

void readScore();
void move_right_one(UserScore** arr, int ind, int curIndex);

// added part finished

#endif
