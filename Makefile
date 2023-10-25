exe: main.o Word_Entry.o
	g++ -g -Wall main.o Word_Entry.o -o exe

main.o: Kondapalli_BST.h Word_Entry.h
	g++ -g -Wall -c Kondapalli_Sreeram_hw5.cpp -o main.o

wordentry.o: Word_Entry.h Word_Entry.cpp
	g++ -g -Wall -c Word_Entry.cpp

clean:
	rm exe *.o

