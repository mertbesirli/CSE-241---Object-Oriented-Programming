output:main.o vector.o set.o container.o
	g++ main.o vector.o set.o container.o -o output
main.o: main.cpp
	g++ -c main.cpp
container.o: container.cpp
	g++ -c container.cpp
set.o: set.cpp
	g++ -c set.cpp
vector.o: vector.cpp
	g++ -c vector.cpp
clean:
	rm *.o output

