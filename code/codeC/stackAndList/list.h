#ifndef list_h
#define list_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "position.h"

typedef struct s_list * List;
typedef struct s_node Node;

//CONSTRUCTEURS :
/*cree une liste vide*/
List initList();

/*ajoute l'Position a sa place*/
void addPos(List *l, Position p);


//PROJECTEURS
/*renvoie vrai si la liste est vide*/
bool emptyList(List l);

/*renvoie vrai si l'Position est le premier
PC : est_premier(l, e) def ssi !vide_liste(l)*/
bool isFirst(List l, Position p);

/*renvoie vrai si l'Position est le dernier
PC : est_dernier(l, e) def ssi !vide_liste(l)*/
bool isLast(List l, Position e);

/*recherche un Position par son nom
PC : recherche_element(l, nom) def ssi !vide_liste(l)*/
Position searchForPos(List l, Position p);

/*supprime l'Position de la liste
PC : supprime_element(l, e) def ssi !vide_liste(l)*/
void deletePos(List *l, Position p);

/*affiche la liste dans l'ordre croissant (vrai) ou decroissant(faux)*/
void printListForward(List l, bool b);

#endif //list_h
