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

typedef struct sGraph *Graph;
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

#endif /* Graph_h */
