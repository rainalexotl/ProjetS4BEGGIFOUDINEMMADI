//
//  TreeOfGameIA.h
//  TreeOfGameIA
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#ifndef TreeOfGameIA_h
#define TreeOfGameIA_h

#include "ReducedGraph.h"
#include "List.h"
#include <stdio.h>

//on lui passe une copie car il faut q'il modifie rien du tout
//la profondeur de recherche peut varier en fonction
void nbGroup(ReducedGraph *rg, int *IA, int *ADV);
int endGame(const Graph g, int *IA, int *ADV, int *bestGroup);
int min(Graph gbis, int profondeur);
int max(Graph gbis, int profondeur);
int heuristique(const Graph g);
int minimax(Graph gbis, int profondeur);
int hasList(const TabHash *tabH, int side1, int side2, int sizeTabH);
bool hasSide(List *l, int side1, int side2);



void cpyReducedGraph(ReducedGraph * rG, const ReducedGraph *rgsrc);
void cpyList(List * l, const List * lsrc);
void cpyHtable (TabHash *tabH, const TabHash *thsrc, int sizeTab);
void cpyGraph (Graph g, const Graph gsrc);
void cpyVertex(Vertex * v, const Vertex * vsrc);
void cpyAdjacents(Vertex ** adj, Vertex ** adjsrc);
Graph newGrpah(const Graph g);
#endif /* TreeOfGameIA */
