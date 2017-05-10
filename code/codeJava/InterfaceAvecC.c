#include <jni.h>
#include <stdio.h>
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include "InterfaceAvecC.h"
/* Define */ //peut etre inutile a voire
#define BLACK '*'
#define WHITE 'o'
#define EMPTY '.'
#define MAXVOISIN 6

/*--------------------------------Coordinates----------------------------------*/
/** Structure Coordinates */
typedef struct sCoordinates {
    int x;
    int y;
} Coordinates;
/** Calcul Fonction */
Coordinates calculateCoordinates(int index, int sizeBoard);
int calculateSquareCoordinates(int x, int y, int sizeBoard);
void postUpCoordinates(Coordinates coord);
/*-----------------------------------------------------------------------------*/
Coordinates calculateCoordinates(int index, int sizeBoard) {
    Coordinates coord;
    coord.x = index/sizeBoard;
    coord.y = index%sizeBoard;
    return coord;
}

int calculateSquareCoordinates(int x, int y, int sizeBoard) {
    return sizeBoard*x+y;
}

void postUpCoordinates(Coordinates coord) {
    printf("x = %d\ny = %d\n", coord.x, coord.y);
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */


/*-----------------------------------PIECE-------------------------------------*/
/** Structure for piece*/
typedef struct sPiece {
    Coordinates coord;
    char color;
}Piece;
/*-----------------------------------------------------------------------------*/
/* Creation fonction */
Piece  createPiece();
/*-----------------------------------------------------------------------------*/
Piece createPiece() {
    Piece p;
    printf("Please enter the colar of the Piece : ");
    scanf("%c", &p.color);
    printf("Please enter the coodinates\n");
    printf("x = ");
    scanf("%d", &p.coord.x);
    printf("y = ");
    scanf("%d", &p.coord.y);
    return p;
}

/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */


/*----------------------------------GRAPH--------------------------------------*/
/** Structure For Graph */
typedef struct sVertex {
    char colar; //colar du noeud reprenté par un caractere
    Coordinates coord; //positionement du Vertex
    struct sVertex **Adjacents;
}Vertex;

struct sGraph {
    int sizeGraph; // la largeur ou la heuteur du graph
    Vertex **s;
};

typedef struct sGraph *Graph;
enum {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, UP_RIGHT = 4, DOWN_LEFT = 5};
//Header for Graph
/** Create Fonction       */
Graph CreateGraph(int sizeGraph);
Vertex *insertVertexGraph(Graph g, int i);
/** Get Fonction          */
int getsizeGraph(const Graph g);
int getNbVertexGraph(const Graph g);
int getW1Graph(int sizeGraph);
int getW2Graph(int sizeGraph);
int getB1Graph(int sizeGraph);
int getB2Graph(int sizeGraph);
//get adjacentUpGraph
int adjacentUpGraph(const Vertex *s, int sizeGraph);
int adjacentDownGraph(const Vertex *s, int sizeGraph);
int adjacentLeftGraph(const Vertex *s, int sizeGraph);
int adjacentRightGraph(const Vertex *s, int sizeGraph);
int adjacentUpRightGraph(const Vertex *s, int sizeGraph);
int adjacentDownLeftGraph(const Vertex *s, int sizeGraph);
/** Modification Fonction */
void replaceVertexGraph(Graph g);
void destroyGraph(Graph g);
/** Observation Fonction  */
bool VertexUpLeftOrDownRightGraph(const Vertex *s, int sizeGraph);
bool VertexUpRightOrDownLeftGraph(const Vertex *s, int sizeGraph);
bool VertexUpRightGraph(const Vertex *s, int sizeGraph);
bool VertexDownLeftGraph(const Vertex *s, int sizeGraph);
/** Print Fonction        */
void postUpCoordGraph(Graph g);
void postUpBoard(Graph g);
void postUpAdjacentsVertex(const Vertex *s);
void postUpSideAdjacentGraph(const Graph g);
/** Calcul Fonction       */
void calculateAdjacentsVertexGraph(Vertex *s, Graph g);
void calculateNbAdjacentsGraph(Graph g);
void calculateSideAdjacentsGraph(int bord, Graph g);

/*---------------------------------             -------------------------------*/

//Implementation Graph
/** Create Fonction */
Graph CreateGraph(int sizeGraph) {
    Graph g = malloc(sizeof(struct sGraph));
    g->sizeGraph = sizeGraph;

    g->s = (Vertex**)malloc(sizeof(Vertex*)*(getNbVertexGraph(g)+4));

    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        g->s[i] = insertVertexGraph(g, i);

    }

    calculateNbAdjacentsGraph(g);
    return g;
}
Vertex *insertVertexGraph(Graph g, int i) {
    Vertex *s = malloc(sizeof(Vertex));

    if (i >= getNbVertexGraph(g) && i < getNbVertexGraph(g)+2) {
        s->colar = WHITE;
    }else if (i >= getNbVertexGraph(g)+2 && i < getNbVertexGraph(g)+4) {
        s->colar = BLACK;
    }else {
        s->colar = EMPTY;
    }
    s->coord = calculateCoordinates(i, getsizeGraph(g));
    return s;
}
/*---------------------------------             -------------------------------*/

/** Calcul Fonction */
//calcule les voisin d'un Vertex donner
void calculateAdjacentsVertexGraph(Vertex *s, Graph g) {
    s->Adjacents = malloc(sizeof(Vertex*)*MAXVOISIN);
    s->Adjacents[UP] = g->s[adjacentUpGraph(s, getsizeGraph(g))];
    s->Adjacents[RIGHT] = g->s[adjacentRightGraph(s, getsizeGraph(g))];
    s->Adjacents[DOWN] = g->s[adjacentDownGraph(s, getsizeGraph(g))];
    s->Adjacents[LEFT] = g->s[adjacentLeftGraph(s, getsizeGraph(g))];

    if (VertexUpRightOrDownLeftGraph(s, getsizeGraph(g))) { //traitement des Vertex les nom des fonction
        if (VertexUpRightGraph(s, getsizeGraph(g))) {        //decrivent le mieux ce qui se fait
            s->Adjacents[UP_RIGHT] = g->s[adjacentDownLeftGraph(s, getsizeGraph(g))];
        }else{
            s->Adjacents[UP_RIGHT] = g->s[adjacentUpRightGraph(s, getsizeGraph(g))]; //ici attention c'est par soucis d'ordre
        }
    }else if (!VertexUpLeftOrDownRightGraph(s, getsizeGraph(g))) {
        s->Adjacents[UP_RIGHT] = g->s[adjacentDownLeftGraph(s, getsizeGraph(g))];
        s->Adjacents[DOWN_LEFT] = g->s[adjacentDownLeftGraph(s, getsizeGraph(g))];
    }

}

//calcul les Adjacents de tous les Vertexs du graph
void calculateNbAdjacentsGraph(Graph g) {
    int taille = getsizeGraph(g);
    for (int i = 0; i < getNbVertexGraph(g); ++i) {
        calculateAdjacentsVertexGraph(g->s[i], g);
    }
    calculateSideAdjacentsGraph(getB1Graph(taille), g);
    calculateSideAdjacentsGraph(getB2Graph(taille), g);
    calculateSideAdjacentsGraph(getW1Graph(taille), g);
    calculateSideAdjacentsGraph(getW2Graph(taille), g);
}


//calcul des Adjacents des 4 bord
void calculateSideAdjacentsGraph(int bord, Graph g) {
    g->s[bord]->Adjacents = (Vertex**)malloc(sizeof(Vertex*)*getsizeGraph(g));
    int j = 0;
    if (bord == getW1Graph(getsizeGraph(g))) {
        for (int i = 0; i < getsizeGraph(g); ++i) {
            g->s[bord]->Adjacents[j++] = g->s[i];
        }
    }else if (bord == getW2Graph(getsizeGraph(g))) {
        for (int i = getNbVertexGraph(g)-getsizeGraph(g); i < getNbVertexGraph(g); ++i) {
            g->s[bord]->Adjacents[j++] = g->s[i];
        }
    }else if (bord == getB1Graph(getsizeGraph(g))) {
        for (int i = 0; i < getNbVertexGraph(g); i += getsizeGraph(g)) {
            g->s[bord]->Adjacents[j++] = g->s[i];
        }
    }else if (bord == getB2Graph(getsizeGraph(g))) {
        for (int i = getsizeGraph(g)-1; i < getNbVertexGraph(g); i += getsizeGraph(g)) {
            g->s[bord]->Adjacents[j++] = g->s[i];
        }
    }
}
/*---------------------------------             -------------------------------*/

/** Get Fonction */
int getsizeGraph(const Graph g) {
    return g->sizeGraph;
}

int getNbVertexGraph(const Graph g) {
    return getsizeGraph(g)*getsizeGraph(g);
}

int getW1Graph(int sizeGraph) {
    return sizeGraph*sizeGraph;
}

int getW2Graph(int sizeGraph) {
    return sizeGraph*sizeGraph+1;
}

int getB1Graph(int sizeGraph) {
    return sizeGraph*sizeGraph+2;
}

int getB2Graph(int sizeGraph) {
    return sizeGraph*sizeGraph+3;
}
/*---------------------------------             -------------------------------*/

/** Adjacent Fonction */
//traintement de Adjacents et Vertex
//trouver le voisin du haut
int adjacentUpGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.x-1 < 0) {
        return getW1Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x-1, s->coord.y, sizeGraph);
}

//calcule du voisin du bas
int adjacentDownGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.x+1 > sizeGraph-1) {
        return getW2Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x+1, s->coord.y, sizeGraph);
}

//voisin de gauche
int adjacentLeftGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.y-1 < 0) {
        return getB1Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x, s->coord.y-1, sizeGraph);
}

//voisin droite
int adjacentRightGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.y+1 > sizeGraph-1) {
        return getB2Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x, s->coord.y+1, sizeGraph);
}

int adjacentUpRightGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.x == 0 && s->coord.y != 0) {
        return getW1Graph(sizeGraph);
    }else if (s->coord.x != 0 && s->coord.y == sizeGraph-1){
        return getB1Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x-1, s->coord.y+1, sizeGraph);
}

int adjacentDownLeftGraph(const Vertex *s, int sizeGraph) {
    if (s->coord.x == sizeGraph-1 && s->coord.y != 0) {
        return getW2Graph(sizeGraph);
    }else if (s->coord.x != 0 && s->coord.y == 0) {
        return getB2Graph(sizeGraph);
    }
    return calculateSquareCoordinates(s->coord.x+1, s->coord.y-1, sizeGraph);
}
/*---------------------------------             -------------------------------*/

/** Observation Fonction */
bool VertexUpLeftOrDownRightGraph(const Vertex *s, int sizeGraph) {
    return ((s->coord.x == 0 && s->coord.y == 0)
            ||(s->coord.x == sizeGraph-1 && s->coord.y == sizeGraph-1));
}

bool VertexUpRightOrDownLeftGraph(const Vertex *s, int sizeGraph) {
    return ((s->coord.x == 0 && s->coord.y == sizeGraph-1)
            || (s->coord.x == sizeGraph-1 && s->coord.y == 0));
}

bool VertexUpRightGraph(const Vertex *s, int sizeGraph) {
    return (s->coord.x == 0 && s->coord.y == sizeGraph-1);
}

bool VertexDownLeftGraph(const Vertex *s, int sizeGraph) {
    return (s->coord.x == sizeGraph-1 && s->coord.y == 0);
}
/*---------------------------------             -------------------------------*/

/** Modification Fonction */
//modificateur
void replaceVertexGraph(Graph g) {
    Piece p = createPiece();
    g->s[calculateSquareCoordinates(p.coord.x, p.coord.y,
        getsizeGraph(g))]->colar = p.color;
}

void destroyGraph(Graph g) {
    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        free(g->s[i]->Adjacents);
        free(g->s[i]);
    }
    free(g);
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */

/*-------------------------IMPLEMENTATION InterfaceAvecC-----------------------*/
JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitPiece (JNIEnv * env, jclass cl, jchar color) {
    jclass piece = (*env)->FindClass(env, "Piece");
    jmethodID mid = (*env)->GetMethodID(env, piece, "<init>", "(C)V");
    jobject object = (*env)->NewObject(env, piece, mid, color);
    return object;
}


JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitHex (JNIEnv * env, jclass cl, jint x, jint y, jchar color) {
    jclass hex = (*env)->FindClass(env, "Hex");
    jmethodID mid = (*env)->GetMethodID(env, hex, "<init>", "(IIC)V");
    jobject object = (*env)->NewObject(env, hex, mid, x, y, color);
    return object;
}

JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitBoard (JNIEnv * env, jclass cl, jint sizeBoard) {
    jclass board = (*env)->FindClass(env, "Board");
    jmethodID mid = (*env)->GetMethodID(env, board, "<init>", "(I)V");
    jobject object = (*env)->NewObject(env, board, mid, sizeBoard);
    return object;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcXCoord (JNIEnv * env, jclass cl, jint i, jint sizeBoard) {
    return calculateCoordinates(i, sizeBoard).x;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcYCoord (JNIEnv * env, jclass cl, jint i, jint sizeBoard) {
    return calculateCoordinates(i, sizeBoard).y;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcPosition (JNIEnv * env, jclass cl, jint x, jint y, jint sizeBoard) {
    return calculateSquareCoordinates(x, y, sizeBoard);
}

/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */
