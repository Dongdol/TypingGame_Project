Prototype.exe: menu.o iswhat.o main.o
	g++ -o Prototype.exe menu.o iswhat.o main.o
menu.o : menu.cpp
	g++ -c -o menu.o menu.cpp
iswhat.o : iswhat.cpp
	g++ -c -o iswhat.o iswhat.cpp
main.o : main.cpp
	g++ -c -o main.o main.cpp
clean :
	rm *.o Prototype.exe
