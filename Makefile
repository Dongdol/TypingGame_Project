Prototype.exe: menu.o TajaGame.o rain.o main.o
	g++ -o Prototype.exe menu.o TajaGame.o rain.o main.o -lncurses -lpthread
menu.o : menu.cpp
	g++ -c -o menu.o menu.cpp -lncurses
TajaGame.o : TajaGame.cpp
	g++ -c -o TajaGame.o TajaGame.cpp -lncurses
main.o : main.cpp
	g++ -c -o main.o main.cpp -lncurses
rain.o : rain.cpp
	g++ -c -o rain.o rain.cpp -lncurses -lpthread
clean :
	rm *.o Prototype.exe
