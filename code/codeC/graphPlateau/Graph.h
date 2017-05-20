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
#include <stdbool.h>
#include <assert.h>
#include "Coordinates.h"
#include "Piece.h"
#include "../accessFiles/FileProcessing.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT Graph
/*-----------------------------------------------------------------------------*/

#define MAXVOISIN 6
#define BLACK '*'
#define WHITE 'o'
#define EMPTY '.'

typedef struct sVertex {
    char color; //color du noeud reprenté par un caractere
    Coordinates coord; //positionement du Vertex
    bool isInGroup; //inform is this vertex is in group
    int groupLeader; //infom the leader of group
    struct sVertex **Adjacents;
}Vertex;

struct sGraph {
    int sizeGraph; // la largeur ou la heuteur du graph
    Vertex **v;
};

typedef struct sGraph *Graph;

enum {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, UP_RIGHT = 4, DOWN_LEFT = 5};

/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
Graph createGraph(int sizeGraph);
Graph createBoardGraph (Graph g, const char *colorTab, int *loaded);

/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
void destroyGraph(Graph g);
void calculateNbAdjacentsGraph(Graph g);
void calculateSideAdjacentsGraph(int board, Graph g);
void replaceVertexGraph(Graph g, int pos, char color);
void calcAdjacentVertexesGraph(Vertex *v, Graph g);
void calcAllAdjacentsGraph(Graph g);
void calcSideAdjacentsGraph(int sidePos, Graph g);

/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
bool isInGroup(const Vertex *v);
bool areAdjacentVertexes(const Vertex *v1, const Vertex *v2);
bool isInSameGroup(const Vertex *v1, const Vertex *v2);
bool isTopLeftOrBottomRightVertexGraph(const Vertex *v, int sizeGraph);

/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
int getSizeGraph(const Graph g);
int getNbVertexGraph(const Graph g);
int getW1Graph(int sizeGraph);
int getW2Graph(int sizeGraph);
int getB1Graph(int sizeGraph);
int getB2Graph(int sizeGraph);
int getGroupLeader(const Vertex *v);

/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
void printCoordGraph(Graph g);
void printBoard(Graph g);
void printAdjSidesGraph(const Graph g);
void printVertexAdjPositions(int posV, Graph g);
void printBoard(Graph g);

/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
#endif /* Graph_h */
