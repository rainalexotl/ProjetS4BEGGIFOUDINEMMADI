.PHONY: all clean maxclean

CC=gcc
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
EXEC=Plateau.out
OBJ= Piece.o Coordinates.o Graph.o  main.o FileProcessing.o ReducedGraph.o List.o HashTable.o
all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

Piece.o : Piece.c
Coordinates.o : Coordinates.c
Graph.o : Graph.c Graph.h
FileProcessing.o : FileProcessing.c
List.o : List.c
HashTable.o : HashTable.c
ReducedGraph.o : ReducedGraph.c
main.o: main.c Graph.h

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC) *.o *.txt *.bi
