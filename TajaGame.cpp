#include "TajaGame.h"

using namespace std;

void Game::Print_Result()
{

    cout<<total_typenum<<endl;
    cout<<fixed;
    cout.precision(1);
    cout << "타자 치는데 걸린 Time: " << type_during_Time << "초" << endl;
    cout << "평균타수: " << ((float)total_typenum / type_during_Time) * 60 <<endl;
    cout << "정확도: " << accuarcy <<"%"<<endl;

    sleep(10);

}


void Game::Remove_Enter(char put_String[], int len)
{
    put_String[len - 1] = '\0';
}


int Game::Return_ErrTypeNum(char Buf[], char put_String[], int str_Size) {
    int err = 0;
    for (int i = 0; i < str_Size; i++) {
        if (Buf[i] != put_String[i])
            err++;
    }

    return err;
}

/*어떤 텍스트로 타자연습할까요~?*/
char* Game::Print_TextList(int select)
{
    string cmp;
    string get;
    char *SelectedFile;
    cout<<"[타자연습 목록]"<<endl;
    for(iter = Text_Mode.begin(); iter != Text_Mode.end(); ++iter)
        cout<<*iter<<"  ";

    while(1)
    {
        cout<<"원하는 글을 입력하세요."<<endl;
        scanf("%s", SelectedFile);
        printf("%s", SelectedFile);
        return SelectedFile;
    }

}

int Game::basicGame()
{
    /*타자연습 언어 선택*/
    int select =0;
    while(1){
        cout<<"어떤 언어로 타자연습을 진행하시겠습니까? 1. 영어 2. 한글"<<endl;
        cin>>select;
        if(select ==SELECT_ENGLISH)
            {
                Text_Mode = English;
                break;
            }
        else if(select==SELECT_HANGUL)
        {
            Text_Mode = Hangul;
            break;
        }
        else
        {
            cout<<"1또는 2를 입력하세요"<<endl;
            continue;
        }
    }

    strcpy(pathName,Print_TextList(select));
    while(getchar() != '\n');
    int fd = open(pathName, O_RDONLY);
    if (fd == -1) {
        perror("Open() Error!");
        exit(-2);
    }
    size_t rsize = 1;
    type_start_Time = (int)time(NULL);

    cout<<"["<<pathName<<"] TypingStart!"<<endl;

    /*한글과 영어 분류하여 타자 연습 */
    if(select == SELECT_ENGLISH)
    {
        while (1) {
        //문자열 초기화
        memset(Buf_E, '\0', SIZE_READ_TEXT_ENG);
        memset(put_String_E, '\0', SIZE_READ_TEXT_ENG);

        rsize = read(fd, Buf_E, SIZE_READ_TEXT_ENG - 1);

        if (rsize == 0) {

            break;
        }

        total_typenum += rsize;

        cout<<Buf_E<<endl; // txt 파일 문자열 출력

        fgets(put_String_E, 100, stdin);
        Remove_Enter(put_String_E, strlen(put_String_E));
        err_typenum += Return_ErrTypeNum(Buf_E, put_String_E, strlen(Buf_E));
        cout<<"오타수:"<<err_typenum<<endl;
        fflush(stdout);
             }
    }
    else if(select == SELECT_HANGUL)
    {
        while (1) {
        //문자열 초기화
        memset(Buf_H, '\0', SIZE_READ_TEXT_HNG);
        memset(put_String_H, '\0', SIZE_READ_TEXT_HNG);

        rsize = read(fd, Buf_H, SIZE_READ_TEXT_HNG );

        if (rsize == 0) {

            break;
        }

        total_typenum += rsize;

        cout<<Buf_H<<endl; // txt 파일 문자열 출력

        fgets(put_String_H, 100, stdin);
        Remove_Enter(put_String_H, strlen(put_String_H));
        err_typenum += Return_ErrTypeNum(Buf_H, put_String_H, strlen(Buf_H));
        cout<<"오타수:"<<err_typenum<<endl;
        fflush(stdout);
             }
    }



    type_during_Time = (int)time(NULL) - type_start_Time;
    accuarcy = (float)(total_typenum - err_typenum)/total_typenum *100;
    total_typenum -= err_typenum; // 오타수만큼 제거

    Print_Result();
    }
