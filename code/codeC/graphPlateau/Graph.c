//
//  Graph.c
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#include "Graph.h"
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include <string.h>
#define MAXVOISIN 6
#define BLACK '*'
#define WHITE 'o'
#define EMPTY '.'

typedef struct sVertex {
    char color; //color du noeud reprenté par un caractere
    Coordinates coord; //positionement du Vertex
    struct sVertex **Adjacents;
}Vertex;

struct sGraph {
    int sizeGraph; // la largeur ou la heuteur du graph
    Vertex **s;
};

/*------------------Recherche des groupes--------------------------*/
Position makePosition(int v){
    // Position p = malloc(sizeof(Position));
    Position p;
    printf("we're in makePosition\n");
    int i;
    p->pos = v;
    p->visited = false;
    for (i = 0; i < MAXVOISIN; i++)
        p->neighbors[i] = NULL;
    return p;
}

Position* makePosTableFromIntTable(int * plays, int nbOfPlays){
    //actual number of plays = nbOfPlays - 2 (the edges)
    int i;
    printf("we are going to make a positions table\n");
    Position * positionTab = (Position*)malloc(sizeof(Position) * (nbOfPlays));
    // Position positionTab[nbOfPlays];
    printf("malloc done\n");
    for (i = 0; i < nbOfPlays; i++){
        positionTab[i] = makePosition(plays[i]);
        printf("pos[%d] = %d\n", i, positionTab[i]->pos);
        // printf("pos[%d] = %d\n", i, positionTab[i]->visited);
    }
    printf("the table is made\n");
    return positionTab;
}

Position makePositionTable(Position p, Vertex * s, const Graph g){
    int i = 0;
    int j = 0;
    int pos;
    
    while (s->Adjacents[i] != NULL){
        // its added to the table only if they share the same color
        if (s->Adjacents[i]->color == g->s[p->pos]->color){
            pos = calculateSquareCoordinates(s->Adjacents[i]->coord.x,
                s->Adjacents[i]->coord.y, g->sizeGraph);

            p->neighbors[j] = makePosition(pos);
            j++;
        }
        i++;
    }
    return p;
}

Position minPosition(Position p, Stack s){
    Position min = p->neighbors[0];
    int i = 1;
    while (p->neighbors[i] != NULL){
        //if its in the stack we consider it visited and continue:
        if (searchStack(s, p->neighbors[i]))
            p->neighbors[i]->visited = true;
        if ((p->neighbors[i]->pos < min->pos) && (!p->neighbors[i]->visited)){
            min = p->neighbors[i];
        }
        i++;
    }
    //??
    min->visited = true;
    return min;
}


int findPositionIndex(Position * positionTable, Position p){
    int i = 0;
    while (positionTable[i] != NULL){
        if (positionTable[i] == p)
            return i;
        else
            i++;
    }
    return i;
}

void pushAndAdd(List *l, Stack *s, Position p){
    push(s, p);
    addPos(l, p);
}

bool allPositionsVisited(Position p){
    int i = 0;
    while (p->neighbors[i] != NULL){
        if (!p->neighbors[i]->visited)
            return false;
    }
    return true;
}

void findGroups(int * plays, int nbOfPlays, List ** groups, int *nbOfGroups, Graph g){
    int i = 0;
    Position min; //la position la plus petite des voisins et n'ayant pas ete visite
    Position * positionTab = makePosTableFromIntTable(plays, nbOfPlays);//the positions of the plays
    List l = initList();
    Stack s = initStack();

    while (plays[i] != -1){
        //the neighbors of the vertex at position plays[i] are calculated...
        calculateAdjacentsVertexGraph(g->s[plays[i]], g);
        i++;
    }

    i = 0;
    while (positionTab[i] != NULL){
        positionTab[i] = makePositionTable(positionTab[i], g->s[plays[i]]->Adjacents[positionTab[i]->pos], g);
    }

    i = 0;
    int goTo; //the index of the position to go to in the position table
    while (positionTab[i] != NULL){
        goTo = i;
        pushAndAdd(&l, &s, positionTab[i]);
        do {
            // pushAndAdd(&s, &l, positionTab[goTo]);
            // min = minPosition(positionTab[goTo]);
            min = minPosition(top(s), s);

            if (allPositionsVisited(positionTab[goTo]))
            //the list is saved before we start search for new ones;
                *groups[*nbOfGroups++] = l; 

            // while (allPositionsVisited(positionTab[goTo])){
            while (allPositionsVisited(top(s))){
                //if all the neighboring positions are visited we remove them
                pop(&s);
                deletePos(&l, top(s));

                //search for the minimum of the new top:
                min = minPosition(top(s), s); 
            }
            pushAndAdd(&l, &s, min);
            goTo = findPositionIndex(positionTab, min);
        } while (!emptyStack(s));
        i++;
    }
}


/*--------------------------------------------------------------------------------------*/

//prototype
void postUpAdjacentsVertex(const Vertex *s);
int getNbVertexGraph(const Graph g);
int getsizeGraph(const Graph g);
Vertex *insertVertexGraph(Graph g, int i, char color);
void calculateAdjacentsVertexGraph(Vertex *s, Graph g);

Graph CreateGraph(int sizeGraph) {
    Graph g = malloc(sizeof(struct sGraph));
    g->sizeGraph = sizeGraph;

    g->s = (Vertex**)malloc(sizeof(Vertex*)*(getNbVertexGraph(g)+4));

    //initialisation des 4 sommets
    for (int i = getNbVertexGraph(g); i < getNbVertexGraph(g)+4; i++) {
        if (i >= getNbVertexGraph(g) && i < getNbVertexGraph(g)+2) {
            g->s[i] = insertVertexGraph(g, i ,WHITE);
        }else {
            g->s[i] = insertVertexGraph(g, i ,BLACK);
        }
    }
    return g;
}

Vertex *insertVertexGraph(Graph g, int i, char color) {
    Vertex *s = malloc(sizeof(Vertex));
    s->color = color;
    s->coord = calculateCoordinates(i, getsizeGraph(g));
    return s;
}

//creation du plateuau de jeu grâce à un tableau de char String en java
Graph CreateBoardGraph (Graph g, const char *colorTab) {
    for (int i = 0; i < getNbVertexGraph(g); i++) {
        g->s[i] = insertVertexGraph(g, i, colorTab[i]);
    }
    return g;
}


/*-------------------------------------------------------------------------------------------------*/
//accesseur

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



/*-------------------------------------------------------------------------------------------------*/
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

//HautGauchOuBasDroite
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





/*-------------------------------------------------------------------------------------------------*/
//modificateur
void replaceVertexGraph(Graph g, int pos, char color) {
    g->s[pos]->color = color;
}


/*--------------------------------------------------------------------------------------------------*/
/* observateur  */

void postUpCoordGraph(Graph g) {
    for (int i = 0; i < 9; ++i) {
        postUpCoordinates(g->s[i]->coord);
    }
}


void postUpBoard(Graph g) {
    for (int i = 0; i < getNbVertexGraph(g); i++) {

        if (i%getsizeGraph(g) == 0/*&& i != 0*/) {
            printf("\n");
            for (int j = 0; j < i/getsizeGraph(g); j++) {
                printf(" ");
            }
        }
        printf("%c ", g->s[i]->color);
    }
    printf("\n\n");
}


void postUpAdjacentsVertex(const Vertex *s) {
    for (int i = 0; i < 4; i++) {
        printf("%c \n", s->Adjacents[i]->color);
    }
}

void postUpSideAdjacentGraph(const Graph g) {
    for (int i = getNbVertexGraph(g); i < getNbVertexGraph(g)+4; i++) {
        printf("%15c\n", g->s[i]->color);
        for (int j = 0; j < getsizeGraph(g); j++) {
            printf("(%d %c %d) ", g->s[i]->Adjacents[j]->coord.x,
            g->s[i]->Adjacents[j]->color, g->s[i]->Adjacents[j]->coord.y);
        }
        printf("\n\n");
    }
}

char * transformGraphToBoardOfChar(const char * fileName){
 	FILE *file = NULL;
    //const char *c;
    int size = 0;
  	//char n[3];
 	char buff[20];
 	char *tab = malloc(sizeof(char)*(size*size+1));
 	char car = 0;
 // 	char fileName[200]="../../config/size";
 // 	sprintf(n,"%d",size);
 // 	strcat(fileName,n);
	// strcat(fileName,".txt");



    int ok = 1;
	file = fopen(fileName, "r");
	if (file) {
		// int i;
        int j;
		// i = 0;
        j = 0;
        ok = 1;
		do {
		    fscanf(file,"%s", buff);
            if (strcmp(buff,"\\dim") == 0) {
                fscanf(file,"%s", buff);
                printf("%s\n", buff);
                size = atoi(buff);
                printf("%d\n", size);
            }
            if (strcmp(buff,"\\board") == 0 && size != 0) {
                while(j < size*size) {
                    fscanf(file, "%c",&car);
                    if (car == '.' || car == '*' || car == 'o') {
                        tab[j++] = car;
                    }
                }
               ok = 0;
            }
        } while (ok);

	}else {
	  printf("%s n'existe pas dans ce repertoire",fileName);
      exit(-1);
	}
	fclose(file);
    return tab;
 }

/*-------------------------------------------------------------------------------------------------*/

void destroyGraph(Graph g) {
    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        //free(g->s[i]->Adjacents);
        free(g->s[i]);
    }
    free(g);
}

//----------------------------------------------------------------------------
//j'initialise le tableau des coups jou�s par un jouer � -1
//int * initPlayerPlays(int sizeBoard) {
//	int size = ((sizeBoard * sizeBoard)/2);
//	int *playerPlays = malloc(sizeof(int)*size);
//	for(int i = 0; i < size; i++ ) {
//		playerPlays[i]=-1;
//	}
//	return(playerPlays);
//}

/*-------------------------------------------------------------------------------------------------*/
//teste De Regression pour le module graph
int testDeRegression() {
    return 1;
}
