

CC=g++
CXXFLAGS=-c -Wall -std=c++11 -g


all: project


project: main.o
	$(CC) main.o -o main
	
main.o: main.cpp
	$(CC) $(CXXFLAGS) main.cpp
	
clean:
	@rm -f *.o
