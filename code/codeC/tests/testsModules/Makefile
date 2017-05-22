.PHONY: all clean maxclean

CC=gcc
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
EXEC=test.out 
OBJ= ../../src/Piece.o ../../src/Coordinates.o ../../src/Graph.o   ../../src/FileProcessing.o ../../src/ReducedGraph.o ../../src/List.o ../../src/HashTable.o GraphTest.o
 
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)
	./test.out
../../src/Piece.o : ../../src/Piece.c
../../src/Coordinates.o : ../../src/Coordinates.c
../../src/Graph.o : ../../src/Graph.c ../../src/Graph.h
../../src/FileProcessing.o : ../../src/FileProcessing.c
../../src/List.o : ../../src/List.c
../../src/HashTable.o : ../../src/HashTable.c
../../src/ReducedGraph.o : ../../src/ReducedGraph.c
GraphTest.o : GraphTest.c ../../src/Graph.h


clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC) *.o *.txt *.bi 
