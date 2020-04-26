Prototype.exe: menu.o TajaGame.o RainGame.o main.o
	g++ -o Prototype.exe menu.o main.o TajaGame.o RainGame.o -lncurses -lpthread
main.o : main.cpp
	g++ -c -o main.o main.cpp -lncurses -lpthread
menu.o : menu.cpp
	g++ -c -o menu.o menu.cpp -lncurses -lpthread
TajaGame.o : TajaGame.cpp
	g++ -c -o TajaGame.o TajaGame.cpp -lncurses -lpthread
RainGame.o : RainGame.cpp
	g++ -c -o RainGame.o RainGame.cpp -lncurses -lpthread
clean :
	rm *.o Prototype.exe
