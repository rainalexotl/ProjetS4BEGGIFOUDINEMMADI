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
ReducedGraph * createReducedGraph(Graph g, TabHash *tabH) {
    ReducedGraph * _rG = malloc(sizeof(ReducedGraph));
    _rG->tabH = tabH;
    _rG->rG = g;
    return _rG;
}
