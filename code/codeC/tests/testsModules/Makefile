.PHONY: all clean maxclean

CC=gcc
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
EXEC=test.out 
OBJ= ../../graphPlateau/Piece.o ../../graphPlateau/Coordinates.o ../../graphPlateau/Graph.o   ../../accessFiles/FileProcessing.o ../../graphPlateau/ReducedGraph.o ../../graphPlateau/List.o ../../graphPlateau/HashTable.o ReducedGraphTest.o
 
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

../../graphPlateau/Piece.o : ../../graphPlateau/Piece.c
../../graphPlateau/Coordinates.o : ../../graphPlateau/Coordinates.c
../../graphPlateau/Graph.o : ../../graphPlateau/Graph.c ../../graphPlateau/Graph.h
../../accessFiles/FileProcessing.o : ../../accessFiles/FileProcessing.c
../../graphPlateau/List.o : ../../graphPlateau/List.c
../../graphPlateau/HashTable.o : ../../graphPlateau/HashTable.c
../../graphPlateau/ReducedGraph.o : ../../graphPlateau/ReducedGraph.c
ReducedGraphTest.o : ReducedGraphTest.c ../../graphPlateau/Graph.h


clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC) *.o *.txt *.bi 
