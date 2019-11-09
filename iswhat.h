#ifndef _ISWHAT_H_
#define _ISWHAT_H_

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
using namespace std;

#define SIZE_READ_TEXT 70 + 3

class Iswhat {
  public:
    int basicgame();
    int Return_ErrTypeNum(char Buf[], char put_String[], int str_Size);
    void Remove_Enter(char put_String[], int len);
     

};

#endif
