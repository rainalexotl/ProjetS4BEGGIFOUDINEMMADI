//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#include "ReducedGraph.h"

/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                        //implement TAD ReducedGraph
/*-----------------------------------------------------------------------------*/
ReducedGraph * createReducedGraph(Graph g) {
    ReducedGraph * _rG = malloc(sizeof(ReducedGraph));
    _rG->rG = g;
    _rG->whiteHashTab = createTabHashRg(getNbVertexGraph(g));
    _rG->blackHashTab = createTabHashRg(getNbVertexGraph(g));
    return _rG;
}
