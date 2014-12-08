

CC=g++
CXXFLAGS=-c -Wall -std=c++11


all: project


project: main.o algo.o
	$(CC) main.o -o main
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
clean:
	@rm -f *.o
