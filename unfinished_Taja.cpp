#include "TajaGame.h"
#include <termios.h>
#define PERMS 0644
//타이핑된 문자열중에 본문과 맞지않는 글자수 반환
//본문과 입력된 문자열을 비교해서 오타수 반환하는 함수

int getch()
{
    int c; 
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


int Game::Return_ErrTypeNum(char Buf[], char put_String[], int str_Size) {
    int err = 0;
    for (int i = 0; i < str_Size; i++) {
        if (Buf[i] != put_String[i])
            err++;
    }

    return err;
}
// fgets()로 받을 때 입력되는 \n 제거하는 함수
void Game::Remove_Enter(char put_String[], int len) {
    put_String[len - 1] = '\0';
}

int Game::basicgame() {
    system("clear");
    ssize_t wsize = 0;
    char pathName[] = "ex";
    char menu[SIZE_READ_TEXT] = {
        '\0',
    };
    char Buf[SIZE_READ_TEXT] = {
        '\0',
    };
    char err_type[SIZE_READ_TEXT] = {
        '\0',
    };
    int total_typenum = 0; //타이핑되는 총 글자수 입력 (공백 포함)
    int err_typenum = 0;
    int fd = open(pathName, O_RDONLY);
    if (fd == -1) {
        perror("open() Error!");
        exit(-2);
    }
	
    size_t rsize = 1;
    int type_start_Time = (int)time(NULL);

    printf("[%s] typing start!\n", pathName);
    while (1) {
        //문자열 초기화
        memset(Buf, '\0', SIZE_READ_TEXT);
        memset(menu, '\0', SIZE_READ_TEXT);

        rsize = read(fd, Buf, SIZE_READ_TEXT - 1);

        if (rsize == 0) {

            break;
        }

        total_typenum += rsize;
	
	printf("%c[32m",27);
        printf("%s\n", Buf); // txt 파일 문자열 출력
	printf("%c[0m",27);
	
	for(int i = 0; menu[i] != '\n'; i++){
	

	menu[i] = getch();

	if(menu[i] == 127 || menu[i] == 8) {
	printf("\b");
	fputs(" ",stdout);
	printf("\b");
	i--;
	i--;
	}
	else if(menu[i] == '\n')
		break;
	else if(menu[i] == '\b')
		printf("ok");
	else
	{
         if(menu[i] == Buf[i]){
                        printf("%c[32m",27);
                        printf("%c",menu[i]);
                        printf("%c[0m",27);
                }
                else if(menu[i] != Buf[i]){
                        printf("%c[31m",27);
                        printf("%c",menu[i]);
                        printf("%c[0m",27);
        	}


	}
	
 
	fflush(stdout);
	}
        Remove_Enter(menu, strlen(menu));
        err_typenum += Return_ErrTypeNum(Buf, menu, strlen(Buf));
	
	printf("\n");	
	printf("오타수: %d\n", err_typenum);
	printf("\n");
        fflush(stdout);
    }

    int type_during_Time = (int)time(NULL) - type_start_Time;
    total_typenum -= err_typenum; // 오타수만큼 제거

    cout << "끝" << endl;
    cout << "타자 치는데 걸린 Time: " << type_during_Time << "초" << endl;
    cout << "타자속도: " << (total_typenum / type_during_Time) * 60 << endl;
	
  
close(fd);
}
