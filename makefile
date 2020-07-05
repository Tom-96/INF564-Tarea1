output: main.o read.o write.o algorithm2.o Strassen2.o
	g++ read.o write.o algorithm2.o Strassen2.o main.o -o exe

write.o: write.cpp write.hpp
	g++ -c write.cpp

read.o: read.cpp read.hpp
	g++ -c read.cpp

algorithm2.o: algorithm2.cpp algorithm2.hpp
	g++ -c algorithm2.cpp

Strassen2.o: Strassen2.cpp Strassen2.hpp
	g++ -c Strassen2.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o exe