//
//  Graph.c
//  graphs
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#include "Graph.h"
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include <string.h>
#define MAXBOARDSIZE 14

/*-----------------------------------------------------------------------------*/
                            //Prototype Of Private Functions
/*-----------------------------------------------------------------------------*/
//prints the color of the vertexes adjacent to the vertex v
void printAdjVertex(const Vertex *v);

//inserts a vertex into the graph g based on its position i and color
Vertex *insertVertexGraph(Graph g, int i, char color);

/*-----------------------------------------------------------------------------*/
//tests if the vertex v is at the top-left or bottom-right corner of the graph
bool isTopLeftOrBottomRightVertexGraph(const Vertex *v, int sizeGraph);

//tests if the vertex v is at the top-right or bottom-left corner of the graph
bool isTopRightOrBottomLeftVertexGraph(const Vertex *v, int sizeGraph);

//tests if the vertex v is at the top-right corner of the graph
bool isTopRightVertexGraph(const Vertex *v, int sizeGraph);

//tests if the vertex v is at the bottom-left corner of the graph
bool isBottomLeftVertexGraph(const Vertex *v, int sizeGraph);

/*-----------------------------------------------------------------------------*/
//returns the position of the the vertex "on-top" of the vertex v
int topAdjVertexGraph(const Vertex *v, int sizeGraph);

//returns the position of the vertex "below" the vertex v
int bottomAdjVertexGraph(const Vertex *v, int sizeGraph);

//returns the position of the vertex on the left of the vertex v
int leftAdjVertexGraph(const Vertex *v, int sizeGraph);

//returns the position of the vertex on the right of the vertex v
int rightAdjVertexGraph(const Vertex *v, int sizeGraph);

//returns the position of the vertex on the "top-right" of the vertex v
int topRightAdjVertexGraph(const Vertex *v, int sizeGraph);

//returns the position of the vertex on the "bottom-left" of the vertex v
int bottomLeftAdjVertexGraph(const Vertex *v, int sizeGraph);

/*-----------------------------------------------------------------------------*/
//calculates the adjacent vertexes of the vertex v
void calcAdjacentVertexesGraph(Vertex *v, Graph g);

//calculates all the adjacent vertex of each vertex of the graph g
void calcAllAdjacentsGraph(Graph g);

//calulcates all theadjacent vertexes of the four sides of the graph
void calcSideAdjacentsGraph(int sidePos, Graph g);
/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
Graph createGraph(int sizeGraph) {
	assert(sizeGraph <= MAXBOARDSIZE );
    Graph g = malloc(sizeof(struct sGraph));
    g->sizeGraph = sizeGraph;

    /* +4 represents the four sides of the graph which are each represented by
    a single vertex */
    g->v = (Vertex**)malloc(sizeof(Vertex*)*(getNbVertexGraph(g)+4));

    //the four sides of the graph already have a specific color
    for (int i = getNbVertexGraph(g); i < getNbVertexGraph(g)+4; i++) {
        if (i >= getNbVertexGraph(g) && i < getNbVertexGraph(g)+2) {
            g->v[i] = insertVertexGraph(g, i ,WHITE);
        }else {
            g->v[i] = insertVertexGraph(g, i ,BLACK);
        }
    }
    return g;
}

Vertex *insertVertexGraph(Graph g, int i, char color) {
	assert(g != NULL);
	assert(color == BLACK || color == WHITE || color == EMPTY);

    struct sVertex *v = malloc(sizeof(struct sVertex));
    v->color = color;
    v->coord = calculateCoordinates(i, getSizeGraph(g));
    v->isInGroup = 0;
    v->groupLeader = -1; //because at the beginning the player, doesn't in a group party
    return v;
}

Graph createBoardGraph (Graph g, const char *colorTab, int *loaded) {
	assert(g != NULL);

    *loaded = 0;
    for (int i = 0; i < getNbVertexGraph(g); i++) {
        if (colorTab[i] != EMPTY)
            *loaded = 1;
        g->v[i] = insertVertexGraph(g, i, colorTab[i]);
    }
    calcAllAdjacentsGraph(g);
    return g;
}

/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
void calcAdjacentVertexesGraph(Vertex *v, Graph g) {
	assert(g != NULL);
	assert(v != NULL);
    v->Adjacents = malloc(sizeof(Vertex*)*MAXADJ);
    for (int i  = 0; i < MAXADJ; i++){
        v->Adjacents[i] = NULL;
    }
    v->Adjacents[UP] = g->v[topAdjVertexGraph(v, getSizeGraph(g))];
    v->Adjacents[RIGHT] = g->v[rightAdjVertexGraph(v, getSizeGraph(g))];
    v->Adjacents[DOWN] = g->v[bottomAdjVertexGraph(v, getSizeGraph(g))];
    v->Adjacents[LEFT] = g->v[leftAdjVertexGraph(v, getSizeGraph(g))];

    if (isTopRightOrBottomLeftVertexGraph(v, getSizeGraph(g))) { //traitement des Vertex les nom des fonction
        if (isTopRightVertexGraph(v, getSizeGraph(g))) {        //decrivent le mieux ce qui se fait
            v->Adjacents[DOWN_LEFT] = g->v[bottomLeftAdjVertexGraph(v, getSizeGraph(g))];
        }else{
            v->Adjacents[UP_RIGHT] = g->v[topRightAdjVertexGraph(v, getSizeGraph(g))]; //ici attention c'est par soucis d'ordre
        }
    }else if (!isTopLeftOrBottomRightVertexGraph(v, getSizeGraph(g))) {
        v->Adjacents[UP_RIGHT] = g->v[topRightAdjVertexGraph(v, getSizeGraph(g))];
        v->Adjacents[DOWN_LEFT] = g->v[bottomLeftAdjVertexGraph(v, getSizeGraph(g))];
    }

}

void calcAllAdjacentsGraph(Graph g) {
	assert (g != NULL);
    int taille = getSizeGraph(g);
    for (int i = 0; i < getNbVertexGraph(g); ++i) {
        calcAdjacentVertexesGraph(g->v[i], g);
    }
    calcSideAdjacentsGraph(getB1Graph(taille), g);
    calcSideAdjacentsGraph(getB2Graph(taille), g);
    calcSideAdjacentsGraph(getW1Graph(taille), g);
    calcSideAdjacentsGraph(getW2Graph(taille), g);
}

void calcSideAdjacentsGraph(int sidePos, Graph g) {
	assert (g != NULL);
	assert (sidePos < getNbVertexGraph(g) + 4);
    g->v[sidePos]->Adjacents = (Vertex**)malloc(sizeof(Vertex*)*getSizeGraph(g));
    int j = 0;
    if (sidePos == getW1Graph(getSizeGraph(g))) {
        for (int i = 0; i < getSizeGraph(g); ++i) {
            g->v[sidePos]->Adjacents[j++] = g->v[i];
        }
    }else if (sidePos == getW2Graph(getSizeGraph(g))) {
        for (int i = getNbVertexGraph(g)-getSizeGraph(g); i < getNbVertexGraph(g); ++i) {
            g->v[sidePos]->Adjacents[j++] = g->v[i];
        }
    }else if (sidePos == getB1Graph(getSizeGraph(g))) {
        for (int i = 0; i < getNbVertexGraph(g); i += getSizeGraph(g)) {
            g->v[sidePos]->Adjacents[j++] = g->v[i];
        }
    }else if (sidePos == getB2Graph(getSizeGraph(g))) {
        for (int i = getSizeGraph(g)-1; i < getNbVertexGraph(g); i += getSizeGraph(g)) {
            g->v[sidePos]->Adjacents[j++] = g->v[i];
        }
    }
}

void replaceVertexGraph(Graph g, int pos, char color) {
	assert(g != NULL);
    assert(pos < getNbVertexGraph(g) );
    assert(color == BLACK || color == WHITE );
    g->v[pos]->color = color;
}

void destroyGraph(Graph g) {
	assert(g != NULL);
    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        free(g->v[i]->Adjacents);
        free(g->v[i]);
    }
    free(g->v);
    free(g);
}

/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
bool isInGroup(const Vertex *v) {
    assert(v);
    return (v->isInGroup);
}

bool areAdjacentVertexes(const Vertex * v1, const Vertex * v2) {
    assert(v1 && v2);
    return(v1->color == v2->color);
}

bool isInSameGroup(const Vertex *v1, const Vertex *v2) {
	assert(v1 && v2);
    return (v1->groupLeader == v2->groupLeader);
}

bool isTopLeftOrBottomRightVertexGraph(const Vertex *v, int sizeGraph) {
	assert(v);
	assert(sizeGraph <= MAXBOARDSIZE );
    return ((v->coord.x == 0 && v->coord.y == 0)
            ||(v->coord.x == sizeGraph-1 && v->coord.y == sizeGraph-1));
}

bool isTopRightOrBottomLeftVertexGraph(const Vertex *v, int sizeGraph) {
	assert(v);
	assert(sizeGraph <= MAXBOARDSIZE );
    return ((v->coord.x == 0 && v->coord.y == sizeGraph-1)
            || (v->coord.x == sizeGraph-1 && v->coord.y == 0));
}

bool isTopRightVertexGraph(const Vertex *v, int sizeGraph) {
	assert(v);
	assert(sizeGraph <= MAXBOARDSIZE );
    return (v->coord.x == 0 && v->coord.y == sizeGraph-1);
}

bool isBottomLeftVertexGraph(const Vertex *v, int sizeGraph) {
	assert(v);
	assert(sizeGraph <= MAXBOARDSIZE );
    return (v->coord.x == sizeGraph-1 && v->coord.y == 0);
}
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
int getSizeGraph(const Graph g) {
	assert(g);
    return g->sizeGraph;
}

int getNbVertexGraph(const Graph g) {
	assert(g);
    return getSizeGraph(g)*getSizeGraph(g);
}

int getW1Graph(int sizeGraph) {
	assert(sizeGraph <= MAXBOARDSIZE );
    return sizeGraph*sizeGraph;
}

int getW2Graph(int sizeGraph) {
	assert(sizeGraph <= MAXBOARDSIZE );
    return sizeGraph*sizeGraph+1;
}

int getB1Graph(int sizeGraph) {
	assert(sizeGraph <= MAXBOARDSIZE );
    return sizeGraph*sizeGraph+2;
}

int getB2Graph(int sizeGraph) {
	assert(sizeGraph <= MAXBOARDSIZE );
    return sizeGraph*sizeGraph+3;
}

int topAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.x-1 < 0) {
        return getW1Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x-1, s->coord.y, sizeGraph);
}

//calcule du voisin du bas
int bottomAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.x+1 > sizeGraph-1) {
        return getW2Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x+1, s->coord.y, sizeGraph);
}

//voisin de gauche
int leftAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.y-1 < 0) {
        return getB1Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x, s->coord.y-1, sizeGraph);
}

//voisin droite
int rightAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.y+1 > sizeGraph-1) {
        return getB2Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x, s->coord.y+1, sizeGraph);
}

int topRightAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.x == 0 && s->coord.y != 0) {
        return getW1Graph(sizeGraph);
    }else if (s->coord.x != 0 && s->coord.y == sizeGraph-1){
        return getB2Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x-1, s->coord.y+1, sizeGraph);
}

int bottomLeftAdjVertexGraph(const Vertex *s, int sizeGraph) {
	assert(s);
	assert(sizeGraph <= MAXBOARDSIZE );
    if (s->coord.x == sizeGraph-1 && s->coord.y != 0) {
        return getW2Graph(sizeGraph);
    }else if (s->coord.x != 0 && s->coord.y == 0) {
        return getB1Graph(sizeGraph);
    }
    return calculateHexCoordinates(s->coord.x+1, s->coord.y-1, sizeGraph);
}

int getGroupLeader(const Vertex *v) {
    assert(v);
    return v->groupLeader;
}

/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
void printCoordGraph(Graph g) {
	assert(g);
    for (int i = 0; i < 9; ++i) {
        printCoordinates(g->v[i]->coord);
    }
}

void printBoard(Graph g) {
	assert(g);
    for (int i = 0; i < getNbVertexGraph(g); i++) {

        if (i % getSizeGraph(g) == 0) {
            printf("\n");
            for (int j = 0; j < i/getSizeGraph(g); j++) {
                printf(" ");
            }
        }
        printf("%c ", g->v[i]->color);
    }
    printf("\n\n");
}

void printAdjVertex(const Vertex *v) {
	assert(v);
    for (int i = 0; i < 4; i++) {
        printf("%c \n", v->Adjacents[i]->color);
    }
}

void printVertexAdjPositions(int posV, Graph g) {
	assert(g);
    int pos = -1;
    for (int i = 0; i < MAXADJ; ++i) {
        if (g->v[posV]->Adjacents[i]) {
            pos = calculateHexCoordinates(g->v[posV]->Adjacents[i]->coord.x,  g->v[posV]->Adjacents[i]->coord.y, getSizeGraph(g));
            printf("(%c %d )\n", g->v[posV]->Adjacents[i]->color, pos);
        }
    }
}

void printAdjSidesGraph(const Graph g) {
	assert(g);
    for (int i = getNbVertexGraph(g); i < getNbVertexGraph(g)+4; i++) {
        printf("%15c\n", g->v[i]->color);
        for (int j = 0; j < getSizeGraph(g); j++) {
            printf("(%d %c %d) ", g->v[i]->Adjacents[j]->coord.x,
            g->v[i]->Adjacents[j]->color, g->v[i]->Adjacents[j]->coord.y);
        }
        printf("\n\n");
    }
}
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
