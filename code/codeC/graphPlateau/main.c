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
    
    int dim(char*fich);
    
    Graph g = CreateGraph(6);
    replaceVertexGraph(g);
    postUpBoard(g);
    postUpSideAdjacentGraph(g);
    destroyGraph(g);
    return 0;
}
