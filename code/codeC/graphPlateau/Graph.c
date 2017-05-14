//
//  Graph.c
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

// si on n'en a pas besoin
#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h> /* utiliser strcmp */
#include <sys/wait.h>
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h> /*constantes symboliques pour les différents types d’ouverture */
#include <dirent.h> /*pour le parcours de repertoire */

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


#define LONG_MAX_NOM 50
#define LONG_MAX_REP 50
#define OK 0
#define ERR_NB_PARAM 1
#define ERR_ACCES_FICHIER 2
#define ERR_CREATION_FIC 3

typedef struct sVertex {
    char color; //color du noeud reprenté par un caractere
    Coordinates coord; //positionement du Vertex
    struct sVertex **Adjacents;
}Vertex;

struct sGraph {
    int sizeGraph; // la largeur ou la heuteur du graph
    Vertex **s;
};

//pritotype
void postUpAdjacentsVertex(const Vertex *s);
int getNbVertexGraph(const Graph g);
int getsizeGraph(const Graph g);
Vertex *insertVertexGraph(Graph g, int i, char color);

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
    int size = 0;
 	char buff[20];
 	char *tab = malloc(sizeof(char)*(size*size));
 	char car = 0;
    int ok = 1;
	file = fopen(fileName, "r");
	if (file) {
		int i,j;
		i = 0;
        j = 0;
        ok = 1;
		do {
		    fscanf(file,"%s", buff);
            if (strcmp(buff,"\\dim") == 0) {
                fscanf(file,"%s", buff);
                //printf("%s\n", buff);
                size = atoi(buff);
                //printf("%d\n", size);
            }
            if (strcmp(buff,"\\board") == 0 && size != 0) {
                while(j < size*size) {
                    fscanf(file, "%c",&car);
                    if (car == '.' || car == '*' || car == 'o') {
                        tab[j++] = car;
                    }
                }
                tab[j] = '\0';
                ok = 0;
            }
        } while (ok);

	}else {
	  fprintf(stderr,"error : %s not found !",fileName);
      exit(-1);
	}
	fclose(file);
    return tab;
 }


void afficheTab(int tab[]) {
    printf("taille = %d\n", tab[0]);
    for (size_t i = 1; i < tab[0]+1; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

 void saveBoardFile(const char * fileName, const char *spots, int BTabGame[], int WTabGame[]) {
     FILE *file = NULL;
     if ((file = fopen(fileName, "w")) == NULL) {
         fprintf(stderr, "error : %s not create\n", fileName);
         exit(-1);
     }

     //configuration du fichier
     //spots[0] = la dimention du fichier
     // i = a global value in this fonction
     int i = 0;
     char buf[5];
     do {
         buf[i] = spots[i];
         i++;
     } while(spots[i] != '#');
     int dim = atoi(buf);
     printf("dim %d\n", dim);
     i = i+1;
     fprintf(file, "\\Hex\n");
     fprintf(file, "\\dim %d\n", dim);
     //save board
     fprintf(file, "\\board\n");
     for (int j = 0; j < dim*dim; j++) {
         if (j%dim == 0 && j != 0) {
             fprintf(file, "\n");
             fprintf(file, "%c ", spots[i++]);
         }else {
             fprintf(file, "%c ", spots[i++]);
         }
     }

     printf("je passe la boucle \n");
     fprintf(file, "\n\\endboard\n");
     fprintf(file, "\\game\n");

     int quiACommencer = spots[i]-48;
     int Bsize = 0;
     int Wsize = 0;
    //  afficheTab(BTabGame);
    //  afficheTab(WTabGame);
     //scanf("%s\n", buf);
     int maxSize = (BTabGame[0] > WTabGame[0])? BTabGame[0] : WTabGame[0];
     int k = 0;
     while (k < maxSize) {
         if (quiACommencer) {
             if (Bsize != BTabGame[0]) {
                 fprintf(file, "\\play * %d %d\n", BTabGame[Bsize+1], BTabGame[Bsize+2]);
                 //printf("taille dest tab de int b = %d w = %d\n", BTabGame[i], WTabGame[i]);
                 Bsize +=2;
             }
             if (Wsize != WTabGame[0]) {
                fprintf(file, "\\play o %d %d\n", WTabGame[Wsize+1], WTabGame[Wsize+2]);
                //printf("taille dest tab de int b = %d w = %d\n", BTabGame[i], WTabGame[i]);
                Wsize +=2;
             }
         }else{
             printf("j'enntre dans le else \n");
             if (Wsize != WTabGame[0]) {
                fprintf(file, "\\play o %d %d\n", WTabGame[Wsize+1], WTabGame[Wsize+2]);
                Wsize +=2;
             }
             if (Bsize != BTabGame[0]) {
                fprintf(file, "\\play * %d %d\n", BTabGame[Bsize+1], BTabGame[Bsize+2]);
                Bsize +=2;
             }
         }
         k++;
     }
     fprintf(file, "\\endgame\n");
     fprintf(file, "\\endhex\n");
     fclose(file);
 }

 void savePlayer(const char * fileNameOfSavePlayer, const char * Bplayer, const char * Wplayer) {
    FILE *file = NULL;
    if ((file = fopen(fileNameOfSavePlayer, "w")) == NULL) {
        fprintf(stderr, "error : %s not create !\n", fileNameOfSavePlayer);
        exit(-1);
    }
    int Bsize = (int)strlen(Bplayer);
    int Wsize = (int)strlen(Wplayer);
    fprintf(file, "\\blackPlayer %d\n", Bsize);
    fprintf(file, "*%s\n", Bplayer);
    fprintf(file, "\\whitePlayer %d\n", Wsize);
    fprintf(file, "o%s\n", Wplayer);
    fclose(file);
}

char * loarPlayer(char color, const char* stringFromFilInC) {
    FILE * file = NULL;
    if ((file = fopen(stringFromFilInC,"r")) == NULL) {
        fprintf(stderr, "error : %s not found !\n", stringFromFilInC);
        exit(-1);
    }
    int ok = 1;
    char buf[50] = {0};
    char *chaine = NULL;
    int size = 0;
    if (color == '*') {
        do {
            fscanf(file, "%s", buf);
            if (strcmp(buf, "\\blackPlayer") == 0) {
                //printf("buf %s\n", buf);
                fscanf(file, "%s\n", buf);
                size = atoi(buf);
                char Bchaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &Bchaine[i]);
                }
                Bchaine[i] = '\0';
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*(size));
                strcpy(chaine, Bchaine);
                ok = 0;
            }
        } while(ok);
    }else {
        do {
            fscanf(file, "%s", buf);
            if (strcmp(buf, "\\whitePlayer") == 0) {
                fscanf(file, "%s\n", buf);
                size = atoi(buf);
                char Wchaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &Wchaine[i]);
                }
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*size);
                strcpy(chaine, Wchaine);
                ok = 0;
            }
        } while(ok);
    }
    return chaine;
}
/*-------------------------------------------------------------------------------------------------*/
//this fonction return the name of save
char ** getSaveFile(const char* NomRep, int *i) {

    char **saveFile = malloc(sizeof(char*)*LONG_MAX_REP);  //
    for (size_t j = 0; j < LONG_MAX_REP; j++) {
        saveFile[j] = malloc(sizeof(char)*40);
    }
    char newEnTeteRep[300];
    struct stat infos;
    DIR *srcDir = NULL;
    struct dirent *fichOuRep = NULL;
    if ((srcDir = opendir(NomRep)) == NULL) {
        perror("Erreur d'ouverture du repertoire\n");
        exit(1);
    }else{
        while ((fichOuRep = readdir(srcDir)) != NULL) {
            if ((strcmp (fichOuRep->d_name, ".") != 0) && (strcmp (fichOuRep->d_name, "..") != 0)
                && (strcmp (fichOuRep->d_name, ".DS_Store") != 0)) {
                //creation du chemin du prochain de mon fichOuRep
                strcpy(newEnTeteRep, NomRep);
                strcat(newEnTeteRep, "/");
                strcat(newEnTeteRep, fichOuRep->d_name);
                if (stat(newEnTeteRep, &infos) == -1) {
                    perror("Erreur stat");
                    exit(2);
                }
                //test si l'on travail avec un repertoire ou un fichier
                //le comportement est different l'appel recursif se fait dans le cas ou c'est un dossier
                if (!S_ISDIR(infos.st_mode)) {
                    strcpy(saveFile[(*i)++], fichOuRep->d_name);
                }
            }
        }
    }
    return saveFile;
}
//We use this foncton to free the saveFile
void freeSaveFile(char** saveFile) {
    for (size_t i = 0; i < LONG_MAX_REP; i++) {
        free (saveFile[i]);
    }
    free(saveFile);
}

/*-------------------------------------------------------------------------------------------------*/

void destroyGraph(Graph g) {
    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        //free(g->s[i]->Adjacents);
        free(g->s[i]);
    }
    free(g);
}

/*-------------------------------------------------------------------------------------------------*/
//teste De Regression pour le module graph
int testDeRegression() {
    return 1;
}

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
