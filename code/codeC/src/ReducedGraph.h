//
//  ReducedGraph.h
//  reducedgraph
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#ifndef ReducedGraph_h
#define ReducedGraph_h

#include "HashTable.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
typedef struct s_ReducedGraph {
    TabHash * whiteHashTab;
    TabHash * blackHashTab;
    Graph g;
} ReducedGraph;

//allocates memory for the reduced graph and its two hash tables
ReducedGraph * createReducedGraph(Graph g);

//reloads all the groups of a graph g, essential if the game has been loaded
ReducedGraph * reloadGroups(Graph g, ReducedGraph *rG);

/*frees the memory allocated for the reduced graph, its graph and its two hash
tables*/
void destroyReducedGraph(ReducedGraph * rG);
/*-----------------------------------------------------------------------------*/

#endif /* ReducedGraph */
