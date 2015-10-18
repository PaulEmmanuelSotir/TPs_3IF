CPP_FLAGS = -Wall -std=c++11

EXE: collection.o main.o
	g++ collection.o main.o -o EXE
main.o: main.cpp dog.h collection.h
	g++ $(CPP_FLAGS) -c main.cpp -o main.o
collection.o: collection.cpp collection.h dog.h
	g++ $(CPP_FLAGS) -c collection.cpp
