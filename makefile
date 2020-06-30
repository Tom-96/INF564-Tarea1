output: main.o algorithm.o Strassen.o
	g++ algorithm.o Strassen.o main.o -o exe

algorithm.o: algorithm.cpp algorithm.hpp
	g++ -c algorithm.cpp

Strassen.o: Strassen.cpp Strassen.hpp
	g++ -c Strassen.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o exe