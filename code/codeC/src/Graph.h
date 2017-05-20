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
#include "FileProcessing.h"
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
//allocates memory for the graph and its array of vertexes
Graph createGraph(int sizeGraph);

//creates the game board from an array of characters passed through Java
Graph createBoardGraph (Graph g, const char *colorTab, int *loaded);

/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
//frees all the memory allocated for the graph g and its vertexes
void destroyGraph(Graph g);

//calculates all the adjacent vertexes of each vertex of the graph g
void calcAllAdjacentsGraph(Graph g);

//calculates all the adjacent vertexes of the four sides of the graph
void calcSideAdjacentsGraph(int sidePos, Graph g);

//replaces a vertex at a position pos with a vertex of the passed color
void replaceVertexGraph(Graph g, int pos, char color);

/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
//tests if a vertex v is in a group
bool isInGroup(const Vertex *v);

//tests if a vertex v1 and a vertex v2 are adjacent
bool areAdjacentVertexes(const Vertex *v1, const Vertex *v2);

//tests if a vertex v1 and a vertex v2 are in the same group
bool isInSameGroup(const Vertex *v1, const Vertex *v2);

/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
//returns the size n of the graph g with n * n vertexes
int getSizeGraph(const Graph g);

//returns the number of vertexes in a graph g
int getNbVertexGraph(const Graph g);

//returns the first white side of the graph
int getW1Graph(int sizeGraph);

//returns the second white side of the graph
int getW2Graph(int sizeGraph);

//returns the first black side of the graph
int getB1Graph(int sizeGraph);

//returns the second black side of the graph
int getB2Graph(int sizeGraph);

//returns the position of the leader of the group that vertex v is in
int getGroupLeader(const Vertex *v);

/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
//prints the coordinates of all the vertexes of the graph g
void printCoordGraph(Graph g);

//prints the graph g in the form of a hex board
void printBoard(Graph g);

//prints the color and coordinates of all the vertexes adjacent to all four sides
void printAdjSidesGraph(const Graph g);

//prints the positions of the vertexes adjacent to the vertex at posV
void printVertexAdjPositions(int posV, Graph g);

/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
#endif /* Graph_h */
