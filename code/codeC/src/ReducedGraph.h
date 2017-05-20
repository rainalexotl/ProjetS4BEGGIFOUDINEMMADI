//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#include "HashTable.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
typedef struct s_ReducedGraph {
    TabHash * whiteHashTab;
    TabHash * blackHashTab;
    Graph rG;
} ReducedGraph;

//allocates memory for the reduced graph and its two hash tables
ReducedGraph * createReducedGraph(Graph g);

//reloads all the groups of a graph g, essential if the game has been loaded
ReducedGraph * reloadGroups(Graph g, ReducedGraph *_rG);

void destroyReducedGraph(ReducedGraph * _rG);
/*-----------------------------------------------------------------------------*/
