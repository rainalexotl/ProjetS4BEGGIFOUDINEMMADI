.PHONY: all clean maxclean

CC=gcc
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
EXEC=test.out 
OBJ=  ../../src/Coordinates.o ../../src/Graph.o   ../../src/FileProcessing.o ../../src/ReducedGraph.o ../../src/List.o ../../src/HashTable.o  tests.o 
 
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)
	./test.out
../../src/Coordinates.o : ../../src/Coordinates.c
../../src/Graph.o : ../../src/Graph.c ../../src/Graph.h
../../src/FileProcessing.o : ../../src/FileProcessing.c
../../src/List.o : ../../src/List.c
../../src/HashTable.o : ../../src/HashTable.c
../../src/ReducedGraph.o : ../../src/ReducedGraph.c
tests.o : tests.c ../../src/ReducedGraph.h


clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC) *.o *.txt *.bi 
