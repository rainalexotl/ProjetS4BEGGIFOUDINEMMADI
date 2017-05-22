.PHONY: all clean maxclean

CC=gcc
CFLAGS= -g -Wall -std=c99
LDFLAGS=-lm
EXEC=TestIA.out
OBJ= ./src/Piece.o \
./src/Coordinates.o \
./src/Graph.o \
./src/TestIA.o \
./src/FileProcessing.o \
./src/ReducedGraph.o \
./src/List.o \
./src/HashTable.o \
./src/TreeOfGameIA.o

all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ./bin/$(EXEC) $(LDFLAGS)
	#@(echo anzilane)
	@(mv ./src/*.o ./obj/)
	./bin/TestIA.out

Piece.o : Piece.c
Coordinates.o : Coordinates.c
Graph.o : Graph.c Graph.h
FileProcessing.o : FileProcessing.c
List.o : List.c
HashTable.o : HashTable.c
ReducedGraph.o : ReducedGraph.c
TreeOfGameIA.o : TreeOfGameIA.c
TestIA.o: TestIA.c 

clean:
	rm -rf ./obj/*.o

maxclean: clean
	  rm -rf ./bin/$(EXEC) ./obj/*.o
