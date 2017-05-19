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
                        //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
ReducedGraph * createReducedGraph(Graph g) {
    ReducedGraph * _rG = malloc(sizeof(ReducedGraph));
    _rG->rG = g;
    _rG->whiteHashTab = createTabHashRg(getNbVertexGraph(g));
    _rG->blackHashTab = createTabHashRg(getNbVertexGraph(g));
    return _rG;
}

ReducedGraph * reloadGroups(Graph g, ReducedGraph *_rG) {
    for (int i = 0; i < getNbVertexGraph(g); i++) {
        if (g->v[i]->color != EMPTY) {
            if (g->v[i]->color == BLACK) {
                searchGroup((*_rG).blackHashTab, g, i, BLACK);
            }else {
                searchGroup((*_rG).whiteHashTab, g, i, WHITE);
            }
        }
    }
    return _rG;
}
