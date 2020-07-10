output: main.o read.o write.o algorithm.o Strassen.o
	g++ read.o write.o algorithm.o Strassen.o main.o -o exev1

write.o: write.cpp write.hpp
	g++ -c write.cpp

read.o: read.cpp read.hpp
	g++ -c read.cpp

algorithm.o: algorithm.cpp algorithm.hpp
	g++ -c algorithm.cpp

Strassen.o: Strassen.cpp Strassen.hpp
	g++ -c Strassen.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o exe