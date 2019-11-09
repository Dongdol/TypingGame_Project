#ifndef _MENU_H_
#define _MENU_H_

#include "TajaGame.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

class Menu {
  public:
    int choice;
    void help();
    void mainmenu();
};

#endif
