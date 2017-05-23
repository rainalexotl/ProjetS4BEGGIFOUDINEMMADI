//
// main.c
//
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//


#include <stdio.h>
#include "Graph.h"
#include "ReducedGraph.h"
#include "TreeOfGameIA.h"
int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    bool joueur = true;
    int stop = 0;
    Piece p;
    int pos;
    int i = 0;
    Graph g = createGraph(4);
    char * str = getSpotsFromFile("../../doc/config/size4.txt");
    g = createBoardGraph(g, str, &i);
    ReducedGraph * rg = createReducedGraph(g);
    printBoard(g);
    while (i < getNbVertexGraph(g) && stop == 0){
        if (joueur){
            //p = createPiece(BLACK);
            //pos = calculateHexCoordinates(p.coord.x, p.coord.y, getSizeGraph(g));

            pos = minimax(g, 3);
            replaceVertexGraph(g, pos, BLACK);
            printf("position du sommet adjacent des sommet \n");
            //postUpPositionAdjacentVertex(pos, g);
            stop = searchGroup(rg->blackHashTab, g, pos, BLACK);
        }else {
            p = createPiece(WHITE);
            pos = calculateHexCoordinates(p.coord.x, p.coord.y, getSizeGraph(g));
            replaceVertexGraph(g, pos, WHITE);
            printf("position du sommet adjacent des sommet \n");
            //postUpPositionAdjacentVertex(pos, g);
            stop = searchGroup(rg->whiteHashTab, g, pos, WHITE);
        }
        printBoard(g);
        joueur = !joueur;
        i++;
    }

    if (stop){
        printf("groupe gagnant trouvé\nvaleur de stop = %d\n", stop);
    }
    free(str);
    destroyReducedGraph(rg);
    destroyGraph(g);
    return 0;
}
