<<<<<<< HEAD
Prototype.exe: menu.o iswhat.o rain.o main.o
	g++ -o Prototype.exe menu.o iswhat.o rain.o main.o -lncurses -lpthread
menu.o : menu.cpp
	g++ -c -o menu.o menu.cpp -lncurses
iswhat.o : iswhat.cpp
	g++ -c -o iswhat.o iswhat.cpp -lncurses
main.o : main.cpp
	g++ -c -o main.o main.cpp -lncurses
rain.o : rain.cpp
	g++ -c -o rain.o rain.cpp -lncurses -lpthread
=======
Prototype.exe: menu.o iswhat.o main.o
	g++ -o Prototype.exe menu.o iswhat.o main.o
menu.o : menu.cpp
	g++ -c -o menu.o menu.cpp
iswhat.o : iswhat.cpp
	g++ -c -o iswhat.o iswhat.cpp
main.o : main.cpp
	g++ -c -o main.o main.cpp
>>>>>>> ba08d4741298b54794e67b7ca524ffc30188a329
clean :
	rm *.o Prototype.exe
