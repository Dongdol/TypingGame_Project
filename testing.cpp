#include "test.h"

int main() {
    Rain Rain;
    Rain.Game_Start();
    return 0;
}

void Rain::Game_Start() {
    pthread_t pthread = 0;
    Rain *arg = new Rain();
    srand(time(NULL));
    clear();
    initscr(); //  curses모드 시작!!

    // score print
    move(1, 0);
    addstr("score :   ");
    sprintf(score_Bar, "%03d", score);
    addstr(score_Bar);

    // hp print
    move(0, 0);
    addstr("life  : ");
    sprintf(hp_Bar, "%03d", hp);
    addstr(hp_Bar);
    refresh();

    // Inventory
    move(2, 0);
    addstr("Inventory: ");
    refresh();

    // Print Stage
    move(0, 74);
    addstr("STAGE1");
    move(1, 60);

    refresh();
    usleep(500000);

    // enter_position
    Draw(19, 0, "--------------------------------------------------------------------------------");
    Draw(20, 20,enter_Bar);
    Draw(21, 0, "--------------------------------------------------------------------------------");

    usleep(500000);

    pthread_create(&pthread, NULL, (THREADFUNCPTR)&Rain::Game_Board, arg);

    while (hp > 0) {

        enter_num = 0;

        for (enter_num = 0; enter_num < 30;) {
            int input = getch();

            if (input == '\n') { //개행 입력 받았을 때

                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기
                FindWords(enter);

                for (int i = 0; i < 30;i++){
                    enter[i] = '\0';
                }

                move(20, 40);
                addstr("                      "); //enter하는 곳 비우기
                Draw(20, 20, enter_Bar);
                move(20, 40);

                break;
            } else if(input == 127){ //백스페이스 눌렀을 때
                enter[enter_num] = '\0'; //개행 문자 널로 바꾸기

                enter[--enter_num] = '\0';
                move(20, 40);
                addstr("                      "); // enter하는 곳 비우기
                move(20, 40);
                addstr(enter);
            } else { //문자 입력할 때
                enter[enter_num++] = input;
                move(20, 40);
                addstr(enter);
            }

            refresh();
        }
    }

    pthread_join(pthread, NULL);
    endwin();
    clear();
}
void Rain::FindWords(char *str) {
    for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter){
        if ((**Iter).str == str) {
            strcpy((**Iter).str, "");
        }
    }
}

void *Rain::Game_Board(void *) {
    while (hp > 0) {
        CreateList();

        //문자열 출력
        for (Iter = WordList.begin(); Iter != WordList.end(); ++Iter) {
            // row가 19이하일 때만 출력한다
            if ((**Iter).row <= 19) {
                Draw((**Iter).row, (**Iter).col, (**Iter).str);
            }

            if ((**Iter).row > 19) {
                pthread_mutex_lock(&lock);
                hp--;
                WordList.pop_front();
                pthread_mutex_unlock(&lock);

                move(0, 0);
                addstr("life  : ");
                sprintf(hp_Bar, "%03d", hp);
                addstr(hp_Bar);
                refresh();
                Iter = WordList.begin();
                // WordList를  pop()해줌에 따라 인덱스 값이 변경 됐으므로 다시
                // 시작
            }
        }

       // Blank_OutputWord();
        move(20, 40);
    }
}

void Rain::Draw(int row, int col, char *str) {
    move(row, col);
    addstr(str);
    refresh();
}

/* void Rain::Print_Words() 			이거 지워도 될듯..?
 {
        srand(time(NULL));

        char** yohan = Get_Words();

        int random =0;
        for(int i= 0; i<10; i++)
        {
                       random = rand()%12;

                       printw("%s",yohan[random]);
        }

         move(5,30);
         printw("%s",yohan[0]);
         refresh();
         usleep(500000);

 }*/

char **Rain::Get_Words() { return STAGE1; }

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
    usleep(1000000);
    Down_Words();
}

char *Return_Str() {
    srand((int)time(NULL));
    int index = rand() % 12;
    return STAGE1[index];
}

void Blank_OutputWord() {
    for (int i = 2; i < 19; i++) {
        move(i, 10);
        addstr("                                                            ");
    }
}
