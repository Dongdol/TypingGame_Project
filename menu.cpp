#include "menu.h"
<<<<<<< HEAD
#include "iswhat.h"
#include "rain.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
=======
>>>>>>> ba08d4741298b54794e67b7ca524ffc30188a329

void Menu::mainmenu() {
    Menu menu;
    Iswhat iswhat;
<<<<<<< HEAD

=======
>>>>>>> ba08d4741298b54794e67b7ca524ffc30188a329
    system("clear"); //콘솔창 초기화
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    cout << " TTTTTTT  Y    Y  PPPPPP  III  N     N   GGG       GGG       A       M   M    EEEEEE "<< endl;
    cout << "    T      Y  Y   P    P   I   NN    N  G         G         A A     M M M M   E      "<< endl;
    cout << "    T       Y     PPPPP    I   N NNN N G   GGG   G   GGG   A   A   M   M   M  EEEEEE "<< endl;
    cout << "    T       Y     P        I   N    NN  G   G     G   G   A AAA A  M       M  E      "<< endl;
    cout << "    T       Y     P       III  N     N   GGG       GGG   A       A M       M  EEEEEE   Ver 1.0" <<endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n[시작하려면 아무키나 누르세요]";
    cin.get();

    while (1) {
        system("clear"); //콘솔창 초기화
<<<<<<< HEAD
        cout << "1.타자 연습 게임" << endl << endl;
        cout << "2.소나기 게임" << endl << endl;
        cout << "3.기록 보기" << endl << endl;
        cout << "4.도움말" << endl << endl;
        cout << "5.종료" << endl << endl;
=======
        printf("1.게임시작\n\n");
        printf("2.기록보기\n\n");
        printf("3.도 움 말\n\n");
        printf("4.게임종료\n\n");
>>>>>>> ba08d4741298b54794e67b7ca524ffc30188a329
        printf("선택>>");
        cin >> menu.choice;
        cin.get();

        switch (menu.choice) {
        case 1:
            iswhat.basicgame(); //기본 타자 연습 모드
            break;
        case 2:
<<<<<<< HEAD
            game();
            break;
        case 3:
            cout << "기록보기함수 \n"; //구현해야함
            break;
        case 4:
            menu.help(); //예시 구현
            break;
        case 5:
=======
            cout << "기록보기함수 \n"; //구현해야함
            break;
        case 3:
            menu.help(); //예시 구현
            break;
        case 4:
>>>>>>> ba08d4741298b54794e67b7ca524ffc30188a329
            system("clear");
            return; //게임 종료
            break;
        default:
            break;
        }
    }
}

void Menu::help() {
    system("clear");

    cout << "타자연습게임입니다" << endl;
    cout << "아무키나 누르면 메인 메뉴로 이동합니다";
    cin.get();
}
