#include "test.h"

int main() {
    Rain Rain;
    Rain.Game_Start();
    return 0;
}

void Rain::Game_Start() {
    pthread_t pthread1 = 0;
    pthread_t pthread2 = 0;
    pthread_t pthread3 = 0;
    Rain *arg = new Rain();
    srand(time(NULL));
    clear();
    initscr(); //  curses모드 시작!!

    // score print
    move(1, 0);
    addstr("score: ");
    sprintf(score_Bar, "%d", score);
    addstr(score_Bar);

    // hp print
    move(0, 0);
    addstr("life: ");
    sprintf(hp_Bar, "%d", hp);
    addstr(hp_Bar);
    refresh();

    // Inventory
    move(2, 0);
    addstr("Inventory: ");
    refresh();

    refresh();
    usleep(500000);

    // enter_position
    Draw(21, 0, "--------------------------------------------------------------------------------");
    Draw(22, 20,enter_Bar);
    Draw(23, 0, "--------------------------------------------------------------------------------");
    usleep(500000);

    //                      Stage1 START
    move(0, 74);
    addstr("STAGE1");
    move(22, 36);

    pthread_create(&pthread1, NULL, (THREADFUNCPTR)&Rain::Game_Board_1, arg);

    while (hp > 0) {

        enter_num = 0;

        for (enter_num = 0; enter_num < 30;) {
            input = getch();

            if (input == '\n') { //개행 입력 받았을 때

                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기
                FindWords(enter);

                for (int i = 0; i < 30;i++){
                    enter[i] = '\0';
                }

                move(22, 36);
                addstr("                      "); //enter하는 곳 비우기
                Draw(22, 20, enter_Bar);
                move(22, 36);

                break;
            } else if(input == 127){ //백스페이스 눌렀을 때
                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기

                enter[--enter_num] = '\0';
                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                move(22, 36);
                addstr(enter);
            } else { //문자 입력할 때
                enter[enter_num++] = input;
                move(22, 36);
                addstr(enter);
            }

           refresh();
        }

        if(score >= 20){
            pthread_cancel(pthread1); //현재 스레드 종료
            for (Iter = WordList.begin(); Iter != WordList.end();) {
                Iter = WordList.erase(Iter);
            }
            break;
        }

    }

    //                      Stage2 START

    move(0, 74);
    addstr("STAGE2");
    move(22, 36);

    pthread_create(&pthread2, NULL, (THREADFUNCPTR)&Rain::Game_Board_2, arg);

    while (hp > 0) {

        enter_num = 0;

        for (enter_num = 0; enter_num < 30;) {
            input = getch();

            if (input == '\n') { //개행 입력 받았을 때

                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기
                FindWords(enter);

                for (int i = 0; i < 30; i++) {
                    enter[i] = '\0';
                }

                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                Draw(22, 20, enter_Bar);
                move(22, 36);

                break;
            } else if (input == 127) {   //백스페이스 눌렀을 때
                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기

                enter[--enter_num] = '\0';
                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                move(22, 36);
                addstr(enter);
            } else { //문자 입력할 때
                enter[enter_num++] = input;
                move(22, 36);
                addstr(enter);
            }

            refresh();
        }

        if (score >= 50) {
            pthread_cancel(pthread2); //현재 스레드 종료
            for (Iter = WordList.begin(); Iter != WordList.end();) {
                Iter = WordList.erase(Iter);
            }
            break;
        }
    }

    //                                              Stage3 START

    move(0, 74);
    addstr("STAGE3");
    move(22, 36);

    pthread_create(&pthread3, NULL, (THREADFUNCPTR)&Rain::Game_Board_3, arg);

    while (hp > 0) {

        enter_num = 0;

        for (enter_num = 0; enter_num < 30;) {
            input = getch();

            if (input == '\n') { //개행 입력 받았을 때

                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기
                FindWords(enter);

                for (int i = 0; i < 30; i++) {
                    enter[i] = '\0';
                }

                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                Draw(22, 20, enter_Bar);
                move(22, 36);

                break;
            } else if (input == 127) {   //백스페이스 눌렀을 때
                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기

                enter[--enter_num] = '\0';
                move(22, 36);
                addstr("                      "); // enter하는 곳 비우기
                move(22, 36);
                addstr(enter);
            } else { //문자 입력할 때
                enter[enter_num++] = input;
                move(22, 36);
                addstr(enter);
            }

            refresh();
        }

        if (score >=70) {
            pthread_cancel(pthread3); //현재 스레드 종료
            for (Iter = WordList.begin(); Iter != WordList.end();) {
                Iter = WordList.erase(Iter);
            }
            break;
        }
    }

    GameComplete();
    sleep(3);
    endwin();
    exit(0);
}

void *Rain::Game_Board_1(void *) {
    pthread_t tid1 = 0;
    while (hp > 0) {
        CreateList_1();

        Blank_OutputWord();
        //문자열 출력
        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 22이하일 때만 출력한다
            if ((**Iter).row < 22) {
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
            }
            if ((**Iter).row > 22) {
                pthread_mutex_lock(&lock);
                hp--;

                if (hp == 0) {
                    GameOver();
                    sleep(5);
                    endwin();
                    exit(0);
                }
                WordList.pop_front();
                pthread_mutex_unlock(&lock);

                move(0, 0);
                addstr("life: ");
                sprintf(hp_Bar, "%d", hp);
                addstr(hp_Bar);
                refresh();

                Iter = WordList.begin();
                // WordList를  pop()해줌에 따라 인덱스 값이 변경 됐으므로
                // 다시 시작
            }
        }
        move(22, 36);
    }
}

void *Rain::Game_Board_2(void *) {

    while (hp > 0) {
        CreateList_2();

        Blank_OutputWord();
        //문자열 출력
        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 22이하일 때만 출력한다
            if ((**Iter).row < 22) {
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
            }
            if ((**Iter).row > 22) {
                pthread_mutex_lock(&lock);
                hp--;

                if (hp == 0) {
                    GameOver();
                    sleep(5);
                    endwin();
                    exit(0);
                }
                WordList.pop_front();
                pthread_mutex_unlock(&lock);

                move(0, 0);
                addstr("life: ");
                sprintf(hp_Bar, "%d", hp);
                addstr(hp_Bar);
                refresh();

                Iter = WordList.begin();
                // WordList를  pop()해줌에 따라 인덱스 값이 변경 됐으므로
                // 다시 시작
            }
        }
        move(22, 36);
    }
}

void *Rain::Game_Board_3(void *) {

    while (hp > 0) {
        CreateList_3();

        Blank_OutputWord();
        //문자열 출력
        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 22이하일 때만 출력한다
            if ((**Iter).row < 22) {
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
            }
            if ((**Iter).row > 22) {
                pthread_mutex_lock(&lock);
                hp--;

                if (hp == 0) {
                    GameOver();
                    sleep(5);
                    endwin();
                    exit(0);
                }
                WordList.pop_front();
                pthread_mutex_unlock(&lock);

                move(0, 0);
                addstr("life: ");
                sprintf(hp_Bar, "%d", hp);
                addstr(hp_Bar);
                refresh();

                Iter = WordList.begin();
                // WordList를  pop()해줌에 따라 인덱스 값이 변경 됐으므로
                // 다시 시작
            }
        }
        move(22, 36);
    }
}
//입력한 단어가 화면에 있는 단어와 일치하면 제거하고 스코어 +10
void Rain::FindWords(char *str) {
    for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
        if (!strcmp((**Iter).str, str)) {
            WordList.erase(Iter);
            Iter = WordList.begin();
            score += 10; //점수 증가
            move(1, 0);
            addstr("score: ");
            sprintf(score_Bar, "%d", score);
            addstr(score_Bar);
            refresh();
            return;
        }
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

// List를 만든다 , rand()는 현재 시간을 기반으로 한 함수이기때문에 1초마다
// 업데이트된다
void Rain::CreateList_1() {
    WordNodePointer word;
    srand((int)time(NULL));
    word = CreateWord(Return_STAGE1());
    WordList.push_back(word);
    usleep(1700000);
    Down_Words();
}
void Rain::CreateList_2() {
    WordNodePointer word;
    srand((int)time(NULL));
    word = CreateWord(Return_STAGE2());
    WordList.push_back(word);
    usleep(1700000);
    Down_Words();
}
void Rain::CreateList_3() {
    WordNodePointer word;
    srand((int)time(NULL));
    word = CreateWord(Return_STAGE3());
    WordList.push_back(word);
    usleep(1500000);
    Down_Words();
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

    return word; //노드 반환
}

char *Return_STAGE1() {
    srand((int)time(NULL));
    int index = rand() % 12;
    return STAGE1[index];
}
char *Return_STAGE2() {
    srand((int)time(NULL));
    int index = rand() % 12;
    return STAGE2[index];
}
char *Return_STAGE3() {
    srand((int)time(NULL));
    int index = rand() % 12;
    return STAGE3[index];
}
void Blank_OutputWord() {
    for (int i = 2; i < 21; i++) {
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
