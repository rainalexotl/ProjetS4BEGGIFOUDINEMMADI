//
//  main.c
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#include <stdio.h>
#include "Graph.h"

int main(int argc, const char * argv[]) {

    // int dim(char*fich);
    // char colors[36] = {0};
    // for (size_t i = 0; i < 6*6; i++) {
    //     colors[i] = '*';
    // }
    char * colors = transformGraphToBoardOfChar(6);

    Graph g = CreateGraph(6);
    //replaceVertexGraph(g);
    g = CreateBoardGraph(g, colors);
    postUpBoard(g);
    //postUpSideAdjacentGraph(g);
    //destroyGraph(g);
    return 0;
}
