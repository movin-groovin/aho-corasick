

CC=g++
CFLAGS=-c -Wall -std=c++11


all: project


project: main.o algo.o
	$(CC) main.o algo.o -o main
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
algo.o:
	$(CC) $(CFLAGS) algo.cpp
	
clean:
	@rm -f *.o
