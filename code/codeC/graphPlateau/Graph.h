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
                            //implement TAD Graph
/*-----------------------------------------------------------------------------*/

#define MAXVOISIN 6
#define BLACK '*'
#define WHITE 'o'
#define EMPTY '.'

typedef struct sVertex {
    char color; //color du noeud reprenté par un caractere
    Coordinates coord; //positionement du Vertex
    bool isInGroup; //inform is this vertex is in group
    int theLeaderOfGroup; //infom the leader of group
    struct sVertex **Adjacents;
}Vertex;

struct sGraph {
    int sizeGraph; // la largeur ou la heuteur du graph
    Vertex **s;
};



typedef struct sGraph *Graph;

enum {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, UP_RIGHT = 4, DOWN_LEFT = 5};

/*-----------------------------------------------------------------------------*/
                            //Create Fonctions
/*-----------------------------------------------------------------------------*/
Graph createGraph(int sizeGraph);
Graph createBoardGraph (Graph g, const char *colorTab, int *loaded);

/*-----------------------------------------------------------------------------*/
                            //Modify Fonctions
/*-----------------------------------------------------------------------------*/
void destroyGraph(Graph g);
void calculateNbAdjacentsGraph(Graph g);
void calculateSideAdjacentsGraph(int board, Graph g);
void replaceVertexGraph(Graph g, int pos, char color);

/*-----------------------------------------------------------------------------*/
                            //Observation Fonctions
/*-----------------------------------------------------------------------------*/
bool isInGroup(const Vertex *v);
bool areVertexAdjacent(const Vertex * v1, const Vertex * v2);
bool isInSameGroup(const Vertex *v1, const Vertex *v2);

/*-----------------------------------------------------------------------------*/
                            //Get Fonctions
/*-----------------------------------------------------------------------------*/
int getsizeGraph(const Graph g);
int getNbVertexGraph(const Graph g);
int getW1Graph(int sizeGraph);
int getW2Graph(int sizeGraph);
int getB1Graph(int sizeGraph);
int getB2Graph(int sizeGraph);
int getLeaderOfGroup(const Vertex *v);

/*-----------------------------------------------------------------------------*/
                            //Post Up Fonctions
/*-----------------------------------------------------------------------------*/
void postUpCoordGraph(Graph g);
void postUpBoard(Graph g);
void postUpSideAdjacentGraph(const Graph g);
void postUpPositionAdjacentVertex(int posV, Graph g);

/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
#endif /* Graph_h */
