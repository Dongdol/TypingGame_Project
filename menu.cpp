#include "RainGame.hpp"
#include "menu.h"
#include "TajaGame.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

short Menu::mainmenu()
 {
   // list<WordNodePointer> WordList;
   // list<WordNodePointer>::iterator Iter;

    Menu menu;
    Game game;
    Rain rain;
    short ON = 1;
    short OFF =0;
    system("clear"); //콘솔창 초기화
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << " TTTTTTT  Y   Y  PPPP  III  N    N   GGG       GGG       A       M   M    EEEEE "<< endl;
    cout << "    T      Y Y   P   P  I   NN   N  G         G         A A     M M M M   E     "<< endl;
    cout << "    T       Y    PPPP   I   N NN N G   GGG   G   GGG   A   A   M   M   M  EEEEE "<< endl;
    cout << "    T       Y    P      I   N   NN  G   G     G   G   A AAA A  M       M  E     "<< endl;
    cout << "    T       Y    P     III  N    N   GGG       GGG   A       A M       M  EEEEE "<<endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n[시작하려면 엔터키[ENTER]를 누르세요.]";
    cin.get();

    system("clear");
    cout << "1.타자 연습 게임" << endl << endl;
    cout << "2.소나기 게임" << endl << endl;
    cout << "3.기록 보기" << endl << endl;
    cout << "4.도움말" << endl << endl;
    cout << "5.종료" << endl << endl;
    printf("선택>>");

        cin>>menu.choice;

        switch (menu.choice) {
        case 1:
            game.basicgame(); //기본 타자 연습 모드
            break;
        case 2:
            while(getchar()!='\n');
            rain.Game_Start(); //산성비 모드
            break;
        case 3:
	    int key;
	    char tok;
            cout << "Select the game you want to see \n"; // taja, rain
            cout << "1. Tajagame        2. Rain" << endl;
            cout << "Select: ";
            cin >> key;

            switch(key) {
            case 1:
                readScore();
                break;
            case 2:
		cout << score << endl;
		cin >> tok;
              //  readRainScore();
                break;
            case 3:
                break;
            }
            break;
        case 4:
            menu.help(); //예시 구현
            break;
        case 5:
            system("clear");
            return OFF; //게임 종료
        default:
            break;

    }
    return ON;
}

void Menu::help()
{
    system("clear");
    getchar();
    cout << "타자연습게임입니다" << endl << endl;

    cout << "1.타자 연습 모드는 한글과 영어를 선택할 수 있습니다." << endl;
    cout << "자신의 오타수와 속도를 확인할 수 있습니다." << endl;
    cout << "게임 진행 중 틀린 글자는 다른 색상으로 표시됩니다!"
    << endl << endl << endl;
    cout << "2.산성비 모드에서는 내려오는 단어를 입력하면 점수가 상승합니다."
         << endl;
    cout << "특정 점수를 만족하면 다음 레벨로 진행됩니다. 영어로 진행됩니다."
         << endl<<endl;
    cout << "1레벨(과일)    100점 충족시 2레벨 진입" << endl<<endl;
    cout << "2레벨(노래 제목)   180점 충족시 3레벨 진입" << endl<<endl;
    cout << "3레벨(학문)    250점 충족시 BOSS레벨 진입" << endl<<endl;
    cout << "BOSS    BOSS HP를 0으로 만들면 게임 클리어" << endl
         << endl
         << endl;

    cout << "엔터 키를 누르시면 메인 메뉴로 이동합니다.\n";

    while(!cin.get());
}
