#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Tool {
  public:
    int choice;
    void help() {
        system("clear");

        cout << "타자연습게임입니다" << endl;
        cout << "아무키나 누르면 메인 메뉴로 이동합니다";
        cin.get();
    }
};

int main() {
    Tool tool;
    printf("\n\n\n\n");
    printf("             타자 연습 게임");
    printf("\n\n\n\n [시작하려면 아무키나 누르세요]");
    cin.get();

    while (1) {
        system("clear"); //콘솔창 초기화
        printf("1.게임시작\n\n");
        printf("2.기록보기\n\n");
        printf("3.도 움 말\n\n");
        printf("4.게임종료\n\n");
        printf("선택>>");
        cin >> tool.choice;
        cin.get();

        switch (tool.choice) {
        case 1:
            cout << "게임 실행 함수 \n"; //구현해야함
            break;
        case 2:
            cout << "기록보기함수 \n"; //구현해야함
            break;
        case 3:
            tool.help(); //예시 구현
            break;
        case 4:
            system("clear");
            return 0; //게임 종료
            break;
        default:
            break;
        }
    }
}
