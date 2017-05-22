//
//  ReducedGraph.h
//  reducedgraph
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.

#include "ReducedGraph.h"

/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                        //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
ReducedGraph * createReducedGraph(Graph g) {
    ReducedGraph * rG = malloc(sizeof(ReducedGraph));
    rG->g = g;
    rG->whiteHashTab = createTabHashRg(getNbVertexGraph(g));
    rG->blackHashTab = createTabHashRg(getNbVertexGraph(g));
    return rG;
}

ReducedGraph * reloadGroups(Graph g, ReducedGraph *rG) {
    for (int i = 0; i < getNbVertexGraph(g); i++) {
        if (g->v[i]->color != EMPTY) {
            if (g->v[i]->color == BLACK) {
                searchGroup((*rG).blackHashTab, g, i, BLACK);
            }else {
                searchGroup((*rG).whiteHashTab, g, i, WHITE);
            }
        }
    }
    return rG;
}

void destroyReducedGraph(ReducedGraph * rG) {
    destroyTabHash(rG->whiteHashTab, getNbVertexGraph(rG->g));
    destroyTabHash(rG->blackHashTab, getNbVertexGraph(rG->g));
    free(rG);
}
