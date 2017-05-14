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
    char * colors = transformGraphToBoardOfChar("../../../SaveFiles/testGame.txt");

    // int i;
    // printf("WhitePositions\n");
    // for (i = 0; i < WNbPlays; i++){
    //     printf("%d\n", WhitePositions[i]->pos);
    // }

    // printf("BlackPositions\n");
    // for (i = 0; i < BNbPlays; i++){
    //     printf("%d\n", BlackPositions[i]->pos);
    // }

    Graph g = CreateGraph(3);
    //replaceVertexGraph(g);
    g = CreateBoardGraph(g, colors);
    postUpBoard(g);
    //postUpSideAdjacentGraph(g);
    //destroyGraph(g);


    int WNbPlays = 7;
    // int BNbPlays = 6;
    int WhitePlays[] = {1, 2, 3, 5, 7, 9, 10};
    // int BlackPlays[] = {0, 4, 11, 6, 8, 12};
    Position * WhitePositions = makePosTableFromIntTable(WhitePlays, WNbPlays);
    printf("the table was returned\n");
    // Position * BlackPositions = makePosTableFromIntTable(BlackPlays, BNbPlays);

    free(WhitePositions);
    // free(BlackPositions);
    return 0;
}
