#include "TajaGame.h"

void Game::Print_Result()
{

    cout<<total_typenum<<endl;
    cout<<fixed;
    cout.precision(1);
    cout << "타자 치는데 걸린 Time: " << type_during_Time << "초" << endl;
    cout << "평균타수: " << ((float)total_typenum / type_during_Time) * 60 <<endl;
    cout << "정확도: " << accuarcy <<"%"<<endl;

    //added func started

    UserScore *user=new UserScore;
    user->spd=(float)total_typenum / type_during_Time*60;
    user->accuracy=accuarcy;
    strcpy(user->text, this->curText);
    strcpy(user->name, this->userName);
    fd=open(SCOREFILE, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if(fd==-1) {
            perror("open() error!");
            exit(-1);
    }

    w_Size=write(fd, (UserScore*)user, sizeof(UserScore));
    if(w_Size==-1) {
            perror("write() error!");
            exit(-2);
    }

    close(fd);

    //added func finished

    err_typenum =0;
    total_typenum =0;
    accuarcy =0.0;
    /*
    while(Text_Mode.size() !=0)
         Text_Mode.pop_back();
         cout<<"dongdol"<<endl;
*/    sleep(3);
}

// added func started
void readScore() {
        int rank=1;
        int index=0;
        char key;
        bool isHigher=false;

        system("clear");        // clear moniter

        cout << "<Records>" << endl << endl;
        cout << "Rank\t\t";
        cout << "Name\t\t";
        cout << "File\t\t";
        cout << "Speed\t\t";
        cout << "Accuracy\t\t" << endl; //UI

        fd=open(SCOREFILE, O_CREAT | O_RDONLY, 0644);
        if(fd==-1) {
                perror("open() error!");
                exit(-1);
        }

        UserScore *user=new UserScore;

        UserScore *user_arr[10];
  r_Size=1;

        while(1) {
                memset(user, '\0', sizeof(UserScore));

                r_Size=read(fd, (UserScore*)user, sizeof(UserScore));
                if(r_Size==-1) {
                        perror("read() error!");
                        exit(-2);
                }       // if an error occurred, exit

                if(r_Size==0)           // no more to read left
                        break;
/*
                if(index==0)    // if there is no node at array, push it
                        user_arr[index++]=user;
                else {
                        for(int i=0; i<index; i++) {
                                cout << user->spd << ", " << user_arr[i]->spd <<endl;
                                if(user->spd > user_arr[i]->spd)
                                        isHigher=true;

                                if(isHigher) {
                                        move_right_one(user_arr, i, index);
                                        user_arr[i]=user;
                                        isHigher=false;
                                        if(index<10)
                                                index++;
                                        break;
                                }
                        }
                        if(index<10) {
                                user_arr[index]=user;
                                if(index != 9)
                                        index++;
                        }
                }
*/

                cout << rank << "\t\t";
                cout << user->name << "\t\t";
                cout << user->text << "\t\t";
                cout << user->spd << "\t\t";
                cout << user->accuracy << "\t\t";
                cout << endl<<endl<<endl;
                rank++;
        }

        close(fd);
        delete user;

        cout << "잠시후 메뉴 화면으로 전환됩니다." << endl;

        sleep(7);
        while (!cin.get());
}

void move_right_one(UserScore** arr, int ind, int curIndex) {
        UserScore *new_arr[10];
        if(curIndex==9) {
                for(int i=ind+1; i<10; i++)
                        new_arr[i]=arr[i-1];
                for(int i=ind+1; i<10; i++)
                        arr[i]=new_arr[i];
        }
        else {
                for(int i=ind+1; i<curIndex+1; i++)
                        new_arr[i]=arr[i-1];
                for(int i=ind+1; i<curIndex+1; i++)
                        arr[i]=new_arr[i];
        }
}
// added func finished

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
        for(iter = Text_Mode.begin(); iter != Text_Mode.end(); ++iter)
        {
            if(iter->compare(SelectedFile) ==0) {
                //
                strcpy(curText, SelectedFile);
                //

                return SelectedFile;
	    }
	    else
                break;
        }
    }

}

int Game::basicgame()
{
        //
    char name[10];
    /*타자연습 언어 선택*/
    cout << "Input your name: ";
    cin >> name;
    strcpy(userName, name);
    //

    while(1){
        system("clear");
        cout<<"어떤 언어로 타자연습을 진행하시겠습니까? 1. 영어 2. 한글"<<endl;
        cin>>select;
        if(select ==SELECT_ENGLISH)
            {
                Text_Mode = English;
                cout<<"영어를 선택하셨습니다."<<endl;
                break;
            }
        else if(select==SELECT_HANGUL)
        {
            Text_Mode = Hangul;
            cout<<"한글을 선택하셨습니다."<<endl;
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
