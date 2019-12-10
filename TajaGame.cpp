#include "TajaGame.h"


char getch()		//getch() 함수 구현
{
    char c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
}




void Game::Print_Result()
{

    cout<<fixed;
    cout.precision(1);
    if(Text_Mode == English){
    cout << "정확도: " << accuarcy <<"%"<<endl; 
    cout <<"오타수: "<<err_typenum-2 << endl;

    }
    cout << "타자 치는데 걸린 Time: " << type_during_Time << "초" << endl;
    cout << "평균타수: " << ((float)total_typenum / type_during_Time) * 60 <<endl;
   
    err_typenum = 0;
    total_typenum = 0;
    accuarcy = 0.0;
    while(Text_Mode.size() != 0)
    {   
        Text_Mode.pop_back(); 
    }
	sleep(3);
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
        for(iter = Text_Mode.begin(); iter != Text_Mode.end(); ++iter)
        {
            if(iter->compare(SelectedFile) ==0)
                return SelectedFile;
        }
    }

}

int Game::basicgame()
{
    /*타자연습 언어 선택*/

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

         printf("%c[32m",27);
        cout << Buf_E << endl; // txt 파일 문자열 출력
        printf("%c[0m",27);
        

        
        for(int i = 0; put_String_E[i] != '\n'; i++){


        put_String_E[i] = getch();

        if(put_String_E[i] == 127 || put_String_E[i] == 8) {
        printf("\b");
        fputs(" ",stdout);
        printf("\b");
        i--;
        i--;
        }
        else if(put_String_E[i] == '\n')
                break;
        else if(put_String_E[i] == '\b')
                printf("ok");
        else
        {
         if(put_String_E[i] == Buf_E[i]){
                        printf("%c[32m",27);
			printf("%c",put_String_E[i]);
                        printf("%c[0m",27);
                }
                else if(put_String_E[i] != Buf_E[i]){
                        printf("%c[31m",27);
                        printf("%c",put_String_E[i]);
                        printf("%c[0m",27);
                }


        }
        

        fflush(stdout);

}

        Remove_Enter(put_String_E, strlen(put_String_E));
        err_typenum += Return_ErrTypeNum(Buf_E, put_String_E, strlen(Buf_E));
        cout<<endl;
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

        printf("%c[32m",27);
        cout << Buf_H << endl; // txt 파일 문자열 출력
        printf("%c[0m",27);
	

	
	for(int i = 0; put_String_H[i] != '\n'; i++){


        put_String_H[i] = getch();
	if(put_String_H[i] == 32){
	printf(" ");
	continue;
	}
	else if(put_String_H[i] == 127 || put_String_H[i] == 8) {
                if(put_String_H[i-1] == 32){
                        printf("\b");
                        fputs(" ",stdout);
                        printf("\b");
                        i-=2;
              		continue;
		  }
		else{
		printf("\b");
		printf("\b");
		fputs(" ",stdout);
		printf("\b");
		i-=4;	
		continue;
		}
        }
	else if(put_String_H[i] == '\n')
                break;

	put_String_H[i+1] = getch();
	put_String_H[i+2] = getch();
	fflush(stdin);
	fflush(stdout);
	
	
	
	
         if(put_String_H[i] == Buf_H[i] && put_String_H[i+1] == Buf_H[i+1] && put_String_H[i+2] == Buf_H[i+2]){
                        printf("%c[32m",27);
                        printf("%c%c%c",put_String_H[i],put_String_H[i+1],put_String_H[i+2]);    
			printf("%c[0m",27);
			

                }
                else{
                        printf("%c[31m",27);
                        printf("%c%c%c",put_String_H[i],put_String_H[i+1],put_String_H[i+2]);
                        printf("%c[0m",27);
                        
   	}
		i+=2;

	
	
 
	fflush(stdin);
	}

        


	
        fgets(put_String_H, 100, stdin);
        Remove_Enter(put_String_H, strlen(put_String_H));
        err_typenum += Return_ErrTypeNum(Buf_H, put_String_H, strlen(Buf_H))/3;  //바이트 수만큼 나눠줘야 오타수 오류x
        cout<<endl;
        fflush(stdout);
             }
    }



    type_during_Time = (int)time(NULL) - type_start_Time;
    accuarcy = (float)(total_typenum - err_typenum)/total_typenum *100;
    total_typenum -= err_typenum; // 오타수만큼 제거

    Print_Result();
    }
