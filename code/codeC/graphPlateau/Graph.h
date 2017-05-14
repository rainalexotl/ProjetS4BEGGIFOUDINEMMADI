//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include "Coordinates.h"
#include "Piece.h"

#include "../stackAndList/list.h"
#include "../stackAndList/stack.h"

typedef struct sGraph *Graph;
typedef struct sVertex Vertex;
enum {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, UP_RIGHT = 4, DOWN_LEFT = 5};

Graph CreateGraph(int sizeGraph);

Graph CreateBoardGraph (Graph g, const char *colorTab);

char* transformGraphToBoardOfChar(const char * fileName);

void calculateNbAdjacentsGraph(Graph g);

void calculateSideAdjacentsGraph(int board, Graph g);

void replaceVertexGraph(Graph g, int pos, char color);

void saveBoardFile(const char * fileName, const char *spots, int BTabGame[], int WTabGame[]);
void savePlayer(const char * fileNameOfSavePlayer, const char * Bplayer, const char * Wplayer);
char * loarPlayer(char color, const char* stringFromFilInC);
char ** getSaveFile(const char* NomRep, int *i);
void freeSaveFile(char** saveFile);


void destroyGraph(Graph g);

//
int getsizeGraph(const Graph g);
int getNbVertexGraph(const Graph g);
//obtenir les 4 sommet
int getW1Graph(int sizeGraph);
int getW2Graph(int sizeGraph);
int getB1Graph(int sizeGraph);
int getB2Graph(int sizeGraph);

void postUpCoordGraph(Graph g);
void postUpBoard(Graph g);
void postUpSideAdjacentGraph(const Graph g);

/*------------------Recherche des groupes--------------------------*/
// void initPositionTable(Position * positions);

Position makePosition(int v);

//takes a table of integers and transforms it into a table of Positions
Position * makePosTableFromIntTable(int * plays, int nbOfPlays);

//creates the table of neighbor positions based on a given one
Position makePositionTable(Position p, Vertex * s, const Graph g);

/*retourne le voisin ayant la position la plus petite, n'ayant pas ete visite*/
Position minPosition(Position p, Stack s);

/*returns the index of a certain position p in a table of positions*/
int findPositionIndex(Position * positionTable, Position p);

//pushes a position p onto the stack s and adds to the list l
void pushAndAdd(List *l, Stack *s, Position p);

/*tests if all the neighboring positions of p are visited*/
bool allPositionsVisited(Position p);

void findGroups(int * plays, int nbOfPlays, List ** groups, int *nbOfGroups, Graph g);

#endif /* Graph_h */
