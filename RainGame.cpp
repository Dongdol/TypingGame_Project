#include "RainGame.hpp"


list<WordNodePointer> WordList;
list<WordNodePointer>::iterator Iter;


void Rain::Game_Start() {
     Rain *arg = new Rain();
    pthread_t pthread = 0;
    
    strcpy(stageName,"STAGE1");
    srand(time(NULL));
    clear();
    initscr(); //  curses모드 시작!!
     
    Print_UI();
    
    usleep(500000);

    pthread_create(&pthread, NULL, (THREADFUNCPTR)&Rain::Game_Board, arg);

    while (hp > 0 || BOSS_HP !=0) {

        enter_num = 0;
        for (enter_num = 0; enter_num < 30;) {
            input = getch();

            if (input == '\n') { //개행 입력 받았을 때

                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기
                FindWords(enter);

                for (int i = 0; i < 30; i++) {
                    enter[i] = '\0';
                }
                attron(COLOR_PAIR(3));
                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                Draw(22, 20, enter_Bar);
                move(22, 36);
                attroff( COLOR_PAIR(3));
                break;
            } else if (input == 127) {   //백스페이스 눌렀을 때
                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기

                enter[--enter_num] = '\0';
                attron( COLOR_PAIR(3));
                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                move(22, 36);
                addstr(enter);
                attroff( COLOR_PAIR(3));
                
            } else { //문자 입력할 때
                   attron(COLOR_PAIR(3));
                enter[enter_num++] = input;
                move(22, 36);
                addstr(enter);
                attroff( COLOR_PAIR(3));
                
            }

           refresh();
        }
    
        if(score==100 && MODE == STAGE1_MODE)
        {
            clear();
            sleep(6);
            Print_UI();
        }

        else if(score == 400 && MODE == STAGE2_MODE)
        {
            sleep(6);
            Print_UI();
        }
        
        else if(score == 700 && STAGE3_MODE)
        {
            sleep(6);
            Print_UI();
        }
       
    }
   
    pthread_join(pthread, NULL);
    Blank_OutputWord();
    refresh();
    endwin();
    clear();
    exit(0);
}
//A_BLINK || A_ITALIC || A_BOLD

void Rain::Print_UI()
{
    start_color();
    short COLOR_USR1;
    init_color(COLOR_USR1,300,300,300);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);//스코어 색상
    init_pair(3,COLOR_WHITE,COLOR_BLACK);//엔터 + 스테이지 색상
    init_pair(4,COLOR_WHITE,COLOR_BLACK);//단어 색상
    // score print
    attrset(A_BOLD);
    move(1, 0);
    addstr("score: ");
    
    sprintf(score_Bar, "%d", score);
    move(1,7);
    attron( COLOR_PAIR(2));
    addstr(score_Bar);
    refresh();
    attroff( COLOR_PAIR(2));
    
    // hp print
   
    move(0, 0);
    addstr("life: ");
    sprintf(hp_Bar, "%d", hp);
    attron( COLOR_PAIR(1));
    addstr(hp_Bar);
    attroff( COLOR_PAIR(1));
    refresh();

    // Inventory
   // move(2, 0);
    //addstr("Inventory: ");
    //refresh();

    // Print Stage
    attron(COLOR_PAIR(3));
    move(0, 74);
    addstr(stageName);
    move(1, 60);
    attroff(COLOR_PAIR(3));

  attroff(COLOR_PAIR(2));
  attron(COLOR_PAIR(3));
    // enter_position
      Draw(21, 0,
         "--------------------------------------------------------------------"
         "------------");
    Draw(22, 20, enter_Bar);
    Draw(23, 0,
         "--------------------------------------------------------------------"
         "------------");
  attroff(COLOR_PAIR(3));
    if(MODE == BOSS_MODE)
    {
        attron(COLOR_PAIR(1));
        move(1,69);
        addstr("BOSS HP: ");
        sprintf(BOSS_HP_BAR,"%d",BOSS_HP);
        addstr(BOSS_HP_BAR);
        refresh();
        attroff(COLOR_PAIR(1));
    }
     refresh();

}

//입력한 단어가 화면에 있는 단어와 일치하면 제거하고 스코어 +10
void Rain::FindWords(char *str) {
    for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter){
        if (!strcmp((**Iter).str,str))
        {   
             WordList.erase(Iter);
             Iter = WordList.begin();

             if(MODE == BOSS_MODE)
             {      
                   BOSS_HP--;
                   attron(COLOR_PAIR(1));
                   move(1,69);
                   addstr("BOSS HP: ");
                  sprintf(BOSS_HP_BAR,"%d",BOSS_HP);
                  addstr(BOSS_HP_BAR);
                  refresh();
                  attroff(COLOR_PAIR(1));
             }
        

             score += SCORE_TYPE;
             move(1, 0);
             addstr("score: ");
             sprintf(score_Bar, "%d", score);
             attron(COLOR_PAIR(2));
             addstr(score_Bar);
             refresh();
              attroff(COLOR_PAIR(2));
             return;
        }
    }
}

void *Rain::Game_Board(void *) {
    while (hp > 0) {
        
        if(score==100 && MODE == STAGE1_MODE)
        {
            SCORE_TYPE = STAGE2_SCORE;
            MODE = STAGE2_MODE;
            memset(stageName,'\0',sizeof(char)*10);
            strcpy(stageName,"STAGE2");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
            
        }
        //단어 입력시 스코어 30으로 변경후 스테이지 변경
        else if(score ==400 && MODE == STAGE2_MODE)
        {
            SCORE_TYPE = STAGE3_SCORE;
            MODE = STAGE3_MODE;
            memset(stageName,'\0',sizeof(char)*10);
            strcpy(stageName,"STAGE3");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        }
        

        else if(score == 700  && MODE == STAGE3_MODE ) 
        {
            SCORE_TYPE = BOSS_SCORE;
            MODE = BOSS_MODE;
            memset(stageName,'\0',sizeof(char)*10);
            strcpy(stageName,"  BOSS");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        }
        
        //보스 HP =0이면 게임을 종료한다
        else if(BOSS_HP ==0 && MODE == BOSS_MODE)
        {
            WordList.clear();
            GameComplete();
            pthread_exit(NULL);
        }
        
        
        CreateList();
        Blank_OutputWord();
        //문자열 출력
        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 19이하일 때만 출력한다
            if ((**Iter).row <21)
            {
                attron( COLOR_PAIR(4) );
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
                 attroff(COLOR_PAIR(4));
            }

            if ((**Iter).row > 22) {
                pthread_mutex_lock(&lock);
                hp--;
                if(hp ==0)
                {
                    
                    GameOver();
                    sleep(5);
                    endwin();
                    pthread_exit(NULL);
                }

                WordList.pop_front();
                pthread_mutex_unlock(&lock);

                move(0, 0);
                addstr("life: ");
                attron(COLOR_PAIR(1));
                sprintf(hp_Bar, "%d", hp);
                addstr(hp_Bar);
                attroff(COLOR_PAIR(1));
                refresh();
                Iter = WordList.begin();
                // WordList를  pop()해줌에 따라 인덱스 값이 변경 됐으므로 다시
                // 시작
            }
        }

       
        move(22, 36);
    }
}

void Rain::Draw(int row, int col, char *str) {
    move(row, col);
    addstr(str);
    refresh();
}



// WordList에 있는 모든 단어들을 2칸씩 내린다
void Rain::Down_Words() {
     
    for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
        (**Iter).row += 2;
    }
}

//노드의 동적할당 및 초기화
WordNodePointer Rain::Initnode(void) {
    WordNodePointer word = new WordNode;

    word->col = 0;
    word->row = 0;
    strcpy(word->str, "");
    return word;
}

// str문자열을 담은 노드를 반환
WordNodePointer Rain::CreateWord(char *str) {
    srand(time(NULL));
    WordNodePointer word = Initnode();
    strcpy(word->str, str);
    word->row = 2;
    word->col = rand() % 40 + 10;

    return word;
}

// List를 만든다 , rand()는 현재 시간을 기반으로 한 함수이기때문에 1초마다
// 업데이트된다
void Rain::CreateList() {
    WordNodePointer word;
    srand((int)time(NULL));

    word = CreateWord(Return_Str());
    WordList.push_back(word);
    if(MODE == BOSS_MODE)
    usleep(600000);
    usleep(2000000);
    Down_Words();
}

char* Rain::Return_Str() {
    srand((int)time(NULL));
    int index = rand() % 13+1;
    
    switch(MODE)
    {
        case STAGE1_MODE:
            return STAGE1[index];
        case STAGE2_MODE:
            return STAGE2[index];
        case STAGE3_MODE:
            return STAGE3[index];
        case BOSS_MODE:
            return BOSS[index%7];
    } 
    
}

void Blank_OutputWord() {
    for (int i = 2; i < 19; i++) {
        move(i, 10);
        addstr("                                                            ");
    }
}


void Rain::GameComplete(){
    clear();
    Blank_OutputWord();
    move(11, 33);
    addstr("YOU DID IT!!!!");
    refresh();
    return;
}

void Rain::GameOver()
{
    clear();
    Blank_OutputWord();
    move(11,33);
    addstr("GameOver...");
    refresh();
    return ;
}

void Rain::StageChange()
{
    char * loading_Str  = new char[30];
    if(MODE == STAGE2_MODE)
    {
        strcpy(loading_Str,"STAGE2");
    }
    else if(MODE == STAGE3_MODE)
    {
        strcpy(loading_Str,"STAGE3");
    }
    else
    {
        strcpy(loading_Str,"BOSS ");
    }
    

    Draw(22,50,"If you play game for long time");
    Draw(23,50,"you can hurt yourself.");
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading.");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading..");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading...");
    usleep(250000);
    Draw(11,22,"                                                      ");
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading.");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading..");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading...");
    usleep(250000);
    Draw(11,22,"                                                      ");
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading.");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading..");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading...");
    usleep(250000);
    Draw(11,22,"                                                      ");
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading.");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading..");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading...");
    usleep(250000);
     Draw(11,22,"                                                      ");
     Draw(11,28,loading_Str);
    Draw(11,35,"Loading.");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading..");
    usleep(250000);
    Draw(11,28,loading_Str);
    Draw(11,35,"Loading...");
    usleep(250000);
    clear();
}

