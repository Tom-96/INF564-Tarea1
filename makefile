 output: main.o Strassen.o
	g++ Strassen.o main.o -o exe

 Strassen.o: Strassen.cpp Strassen.hpp
	g++ -c Strassen.cpp

 main.o: main.cpp
	g++ -c main.cpp

 clean:
	rm *.o exe