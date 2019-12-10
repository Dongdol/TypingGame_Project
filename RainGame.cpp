#include "RainGame.hpp"

list<WordNodePointer> WordList;
list<WordNodePointer>::iterator Iter;

void Rain::Game_Start() {
    Rain *arg = new Rain();
    short COLOR_USR1;
    initscr(); // curses모드 시작!!

    pthread_create(&pthread, NULL, (THREADFUNCPTR)&Rain::Game_Board, arg);
    start_color();
    init_color(COLOR_USR1, 300, 300, 300);
    attrset(A_BOLD);
    sleep(5);
    Print_UI();

    while (hp > 0 || BOSS_HP != 0) {

        enter_num = 0;
        for (enter_num = 0; enter_num < 30;) {
            if (hp == 0) {
                pthread_exit(NULL);
            }
            if (BOSS_HP == 0) {
                pthread_exit(NULL);
            }
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
                attroff(COLOR_PAIR(3));
                break;
            } else if (input == 127) { //백스페이스 눌렀을 때
                if (enter_num > 0) {
                    enter[--enter_num] = '\0';
                    attron(COLOR_PAIR(3));
                    move(22, 36);
                    addstr("                      "); // enter하는 곳 비우기
                    move(22, 36);
                    addstr(enter);
                    attroff(COLOR_PAIR(3));
                } else {
                    move(22, 36);
                    addstr("                      "); // enter하는 곳 비우기
                    move(22, 36);
                }
            } else { //문자 입력할 때
                attron(COLOR_PAIR(3));
                enter[enter_num++] = input;
                move(22, 36);
                addstr(enter);
                attroff(COLOR_PAIR(3));
            }

            refresh();
        }

        if (score == 50 && MODE == STAGE1_MODE) // 2단계
        {
            clear();
            sleep(6);
            Print_UI();
        } else if (score == 150 && MODE == STAGE2_MODE) // 3단계
        {
            sleep(6);
            Print_UI();
        }

        else if (score == 270 && STAGE3_MODE) // 보스
        {
            sleep(6);
            Print_UI();
        }
    }

    pthread_join(pthread, NULL);
    Blank_OutputWord();
    refresh();
    clear();
    endwin();
    return;
}
// A_BLINK || A_ITALIC || A_BOLD

void Rain::Print_UI() {
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK); //스코어 색상
    init_pair(3, COLOR_WHITE, COLOR_BLACK); //엔터 + 스테이지 색상
    init_pair(4, COLOR_WHITE, COLOR_BLACK); //단어 색상
    // score print

    move(1, 0);
    addstr("score: ");

    sprintf(score_Bar, "%d", score);
    move(1, 7);
    attron(COLOR_PAIR(2));
    addstr(score_Bar);
    refresh();
    attroff(COLOR_PAIR(2));

    // hp print

    move(0, 0);
    addstr("life: ");
    sprintf(hp_Bar, "%d", hp);
    attron(COLOR_PAIR(1));
    addstr(hp_Bar);
    attroff(COLOR_PAIR(1));
    refresh();

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
    if (MODE == BOSS_MODE) {
        attron(COLOR_PAIR(1));
        move(1, 69);
        addstr("BOSS HP: ");
        sprintf(BOSS_HP_BAR, "%d", BOSS_HP);
        addstr(BOSS_HP_BAR);
        refresh();
        attroff(COLOR_PAIR(1));
    }
    refresh();
}

//입력한 단어가 화면에 있는 단어와 일치하면 제거하고 스코어 +10
void Rain::FindWords(char *str) {
    for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
        if (!strcmp((**Iter).str, str)) {
            WordList.erase(Iter);
            Iter = WordList.begin();

            if (MODE == BOSS_MODE) {
                BOSS_HP--;
                attron(COLOR_PAIR(1));
                move(1, 69);
                addstr("BOSS HP: ");
                sprintf(BOSS_HP_BAR, "%d", BOSS_HP);
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
    int count = 0;
    while (hp > 0) {
        if (score == 0 && MODE == START_MODE) { // 1단계
            SCORE_TYPE = STAGE1_SCORE;
            MODE = STAGE1_MODE;
            memset(stageName, '\0', sizeof(char) * 10);
            strcpy(stageName, "STAGE1");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        } else if (score == 50 && MODE == STAGE1_MODE) // 2단계
        {
            SCORE_TYPE = STAGE2_SCORE;
            MODE = STAGE2_MODE;
            memset(stageName, '\0', sizeof(char) * 10);
            strcpy(stageName, "STAGE2");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        }
        //단어 입력시 스코어 30으로 변경후 스테이지 변경
        else if (score == 150 && MODE == STAGE2_MODE) // 3단계
        {
            SCORE_TYPE = STAGE3_SCORE;
            MODE = STAGE3_MODE;
            memset(stageName, '\0', sizeof(char) * 10);
            strcpy(stageName, "STAGE3");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        } else if (score == 270 && MODE == STAGE3_MODE) // 보스
        {
            SCORE_TYPE = BOSS_SCORE;
            MODE = BOSS_MODE;
            memset(stageName, '\0', sizeof(char) * 10);
            strcpy(stageName, "  BOSS");
            WordList.clear();
            Blank_OutputWord();
            clear();
            StageChange();
        }
        //보스 HP =0이면 게임을 종료한다
        else if (BOSS_HP == 0 && MODE == BOSS_MODE) {
            // WordList.clear();
            GameComplete();
            pthread_exit(NULL);
        }

        CreateList();
        Blank_OutputWord();
        //문자열 출력

        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 21이하일 때만 출력한다

            if ((**Iter).row < 21) {
                attron(COLOR_PAIR(4));
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
                attroff(COLOR_PAIR(4));
            }
            if ((**Iter).row > 22) {

                pthread_mutex_lock(&lock);
                hp--;
                WordList.pop_front();
                pthread_mutex_unlock(&lock);
                if (hp == 0) {
                    GameOver();
                    pthread_exit(NULL);
                }
                move(0, 0);
                addstr("                      ");
                move(0, 0);
                addstr("life: ");
                attron(COLOR_PAIR(1));
                sprintf(hp_Bar, "%d", hp);
                addstr(hp_Bar);
                attroff(COLOR_PAIR(1));
                refresh();
                Iter = WordList.begin();
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
    if (MODE == BOSS_MODE)
        usleep(600000);
    usleep(2000000); // 2000000
    Down_Words();
}

char *Rain::Return_Str() {
    srand((int)time(NULL));
    int index = rand() % 30;

    switch (MODE) {
    case STAGE1_MODE:
        return STAGE1[index % 19];
    case STAGE2_MODE:
        return STAGE2[index];
    case STAGE3_MODE:
        return STAGE3[index];
    case BOSS_MODE:
        return BOSS[index % 12];
    }
}

void Blank_OutputWord() {
    for (int i = 2; i < 21; i++) {
        move(i, 10);
        addstr("                                                            ");
    }
}

void Rain::GameComplete() {
    clear();
    Blank_OutputWord();
    Draw(8, 8, "  V     V  III   CCC  TTTTT  OOO   RRRR   Y   Y   !! !!  ");
    Draw(9, 8, "  V     V   I   C   C   T   O   O  R   R   Y Y    !! !!  ");
    Draw(10, 8, "   V   V    I   C       T   O   O  RRRR     Y     !! !!  ");
    Draw(11, 8, "    V V     I   C   C   T   O   O  R  R     Y            ");
    Draw(12, 8, "     V     III   CCC    T    OOO   R   R    Y     !! !!  ");
    Draw(21, 23, "To Restart, Press the [ENTER]");
    refresh();
    sleep(5);
    clear();
    endwin();

    system("./Prototype.exe"); //프로그램 재시작
}

void Rain::GameOver() {
    clear();
    Blank_OutputWord();
    Draw(8, 2,
         "    GGG       A       M   M    EEEEE   OOO   V     V EEEEE  RRRR     "
         "  ");
    Draw(9, 2,
         "   G         A A     M M M M   E      O   O  V     V E      R   R    "
         "  ");
    Draw(10, 2,
         "  G   GGG   A   A   M   M   M  EEEEE  O   O   V   V  EEEEE  RRRR     "
         "  ");
    Draw(11, 2,
         "   G   G   A AAA A  M       M  E      O   O    V V   E      R  R     "
         "  ");
    Draw(12, 2,
         "    GGG   A       A M       M  EEEEE   OOO      V    EEEEE  R   R "
         ".....");
    Draw(21, 23, "To Restart, Press the [ENTER]");
    refresh();
    sleep(5);
    clear();
    endwin();

    system("./Prototype.exe"); //프로그램 재시작
}

void Rain::StageChange() {
    char *loading_Str = new char[30];

    if (MODE == STAGE1_MODE) {
        strcpy(loading_Str, "STAGE1");
    } else if (MODE == STAGE2_MODE) {
        strcpy(loading_Str, "STAGE2");
    } else if (MODE == STAGE3_MODE) {
        strcpy(loading_Str, "STAGE3");
    } else {
        strcpy(loading_Str, "BOSS");
    }

    Draw(22, 50, "If you play game for long time");
    Draw(23, 50, "you can hurt yourself.");
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading.");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading..");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading...");
    usleep(250000);
    Draw(11, 22, "                                                      ");
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading.");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading..");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading...");
    usleep(250000);
    Draw(11, 22, "                                                      ");
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading.");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading..");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading...");
    usleep(250000);
    Draw(11, 22, "                                                      ");
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading.");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading..");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading...");
    usleep(250000);
    Draw(11, 22, "                                                      ");
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading.");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading..");
    usleep(250000);
    Draw(11, 28, loading_Str);
    Draw(11, 35, "Loading...");
    usleep(250000);
    clear();
}
