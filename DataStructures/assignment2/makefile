output: main.o TextEditor.o Sequence.o
	g++ Sequence.o TextEditor.o main.o -o output 

main.o: main.cpp
	g++ -c main.cpp

TextEditor.o: TextEditor.cpp TextEditor.h
	g++ -c TextEditor.cpp

Sequence.o: Sequence.cpp Sequence.h
	g++ -c Sequence.cpp

clean:
	rm *.o output